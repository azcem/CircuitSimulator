#include "solve.hpp"
#include "Elements/Element.hpp"
#include "constants.hpp"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <list>

double i_emitter(double v_be, double v_bc) {
	return -1 * I_SAT_EMITTER * (exp(v_be/V_T_EMITTER) - 1) + ALPHA_R * I_SAT_COLLECTOR * (exp(v_bc/V_T_COLLECTOR) - 1);
}

double i_collector(double v_be, double v_bc) {
	return ALPHA_F * I_SAT_EMITTER * (exp(v_be/V_T_EMITTER) - 1) - I_SAT_COLLECTOR * (exp(v_bc/V_T_COLLECTOR) - 1);
}

double i_base(double v_be, double v_bc) {
	return -1 * (i_collector(v_be, v_bc) + i_emitter(v_be, v_bc));
}

double g_ee(double v_b, double v_e) {
	return I_SAT_EMITTER/V_T_EMITTER * exp((v_b - v_e)/V_T_EMITTER);
}

double g_ec(double v_b, double v_c) {
	return ALPHA_R * I_SAT_COLLECTOR / V_T_COLLECTOR * exp((v_b - v_c)/V_T_COLLECTOR);
}

double g_ce(double v_b, double v_e) {
	return ALPHA_F * I_SAT_EMITTER/V_T_EMITTER * exp((v_b - v_e)/V_T_EMITTER);
}

double g_cc(double v_b, double v_c) {
	return I_SAT_COLLECTOR / V_T_COLLECTOR * exp((v_b - v_c)/V_T_COLLECTOR);
}

double I_eq_diode(double id, double G_eq, double v_positive, double v_negative) {
	return id - G_eq * (v_positive - v_negative);
}

double G_eq_diode(double v_positive, double v_negative) {
	return I_SAT_DIODE/V_T_DIODE * exp((v_positive - v_negative)/V_T_DIODE);
}

double i_diode(double v_positive, double v_negative) {
	return I_SAT_DIODE * (exp((v_positive-v_negative)/V_T_DIODE) - 1);
}

double i_drain(double v_gs, double v_ds) {
	if (v_gs <= V_t_MOSFET) {
		return 0;
	} else if (v_ds >= 0 && v_ds <= (v_gs - V_t_MOSFET)) {
		return BETA * ((v_gs - V_t_MOSFET)*v_ds - 0.5 * v_ds*v_ds);
	} else {
		return BETA/2 * pow(v_gs - V_t_MOSFET, 2) * (1 + LAMBDA * v_ds);
	}
}

double i_source(double v_gs, double v_ds) {
	return -1 * i_drain(v_gs, v_ds);
}

double i_gate(double v_gs, double v_ds) { return 0; }

double G_ds(double v_gs, double v_ds) {
	if (v_gs <= V_t_MOSFET) {
		return 0;
	} else if (v_ds >= 0 && v_ds <= (v_gs - V_t_MOSFET)) {
		return BETA * (v_gs - V_t_MOSFET - v_ds);
	} else {
		return BETA/2 * LAMBDA * pow(v_gs - V_t_MOSFET, 2);
	}
}

double g_m_MOSFET(double v_gs, double v_ds) {
	if (v_gs <= V_t_MOSFET) {
		return 0;
	} else if (v_ds >= 0 && v_ds <= (v_gs - V_t_MOSFET)) {
		return BETA * v_ds;
	} else {
		return BETA * (v_gs - V_t_MOSFET) * (1 + LAMBDA * v_ds);
	}
}

/*Ad-hoc class for calculating Hg(x)*/
Hg::Hg(Element element, int size) {
	m_elementType = element.getName()[0];
	m_size = size;
	if (m_elementType == "D") {
		m_negativeNode = element["negativeNode"]; m_positiveNode = element["positiveNode"];
	} else if (m_elementType == "Q") {
		m_base = element["base"]; m_collector = element["collector"]; m_emitter = element["emitter"];
	} else {
		m_source = element["source"]; m_gate = element["gate"]; m_drain = element["drain"];
	}
}

VectorXd Hg::operator()(VectorXd& xk) {
	VectorXd xk_(m_size+1);
	xk_ << 0, xk;
	VectorXd xk1(m_size+1);
	if (m_elementType == "D") {
		double i_d = i_diode(xk_(m_positiveNode), xk_(m_negativeNode));
		xk1(m_positiveNode) = i_d;
		xk1(m_negativeNode) = -i_d;
	} else if (m_elementType == "Q") {
		double v_b = xk_(m_base); double v_c = xk_(m_collector); double v_e = xk_(m_emitter);
		double ib = i_base(v_b - v_e, v_b - v_c);
		double ic = i_collector(v_b - v_e, v_b - v_c);
		double ie = i_emitter(v_b - v_e, v_b - v_c);
		xk1(m_emitter) = ie;
		xk1(m_collector) = ic;
		xk1(m_base) = ib;
	} else {
		double v_d = xk_(m_drain); double v_s = xk_(m_source); double v_g = xk_(m_gate);
		double id = i_drain(v_g - v_s, v_d - v_s);
		double ig = i_gate(v_g - v_s, v_d - v_s);
		double is = i_source(v_g - v_s, v_d - v_s);
		xk1(m_drain) = id;
		xk1(m_gate) = ig;
		xk1(m_source) = is;
	}
	return xk1(Eigen::lastN(m_size));
}

std::vector<Hg> getH_and_g(std::vector<Element>& nonlinearElements, int size) {
	std::vector<Hg> vec;
	for (auto element : nonlinearElements) {
		auto hg = Hg(element, size);
		vec.push_back(hg);
	}
	return vec;
}

VectorXd solveLinearCircuit(MatrixXd& A, VectorXd& b) {
	return A.partialPivLu().solve(b);
}

/*stamping nonlinear devices*/
std::pair<MatrixXd, VectorXd> getJacobianAndRHS(std::list<Element>& nonLinearElements, int numNodes, int numGroup2, VectorXd xk) {
	int size = numNodes + numGroup2 + 1;
	MatrixXd J(size, size);
	VectorXd rhs(size);
	VectorXd xk_;
	xk_ << 0, xk;
	for (auto element : nonLinearElements) {
		std::string elementName = element.getName();
		if (elementName[0] == 'D') {
			int positiveNode = element["positiveNode"]; int negativeNode = element["negativeNode"];
			double v_pos = xk_(positiveNode); double v_neg = xk_(negativeNode);
			double Geq = G_eq_diode(v_pos, v_neg);
			double id = i_diode(v_pos, v_neg);
			double Ieq = I_eq_diode(id, Geq, v_pos, v_neg);
			J(positiveNode, positiveNode) += Geq;
			J(negativeNode, negativeNode) += Geq;
			J(positiveNode, negativeNode) -= Geq;
			J(negativeNode, positiveNode) -= Geq;
			rhs(positiveNode) -= Ieq;
			rhs(negativeNode) += Ieq;
		} else if (elementName[0] == 'Q') {
			int base = element["base"]; int collector = element["collector"]; int emitter = element["emitter"];
			double v_b = xk_(base); double v_c = xk_(collector); double v_e = xk_(emitter);
			double gee = g_ee(v_b, v_e);
			double gec = g_ec(v_b, v_c);
			double gce = g_ce(v_b, v_e);
			double gcc = g_cc(v_b, v_c);
			double ie = i_emitter(v_b - v_e,v_b - v_c);
			double ic = i_collector(v_b - v_e, v_b - v_c);
			double Ie = ie + gee * (v_b - v_e) - gec * (v_b - v_c);
			double Ic = ic - gce * (v_b - v_e) - gcc * (v_b - v_c);
			J(emitter, emitter) += gee;
			J(emitter, collector) -= gec;
			J(emitter, base) += (gec - gee);
			J(collector, emitter) -= gce;
			J(collector, collector) += gcc;
			J(collector, base) += (gce - gcc);
			J(base, emitter) += (gce - gee);
			J(base, collector) += (gec - gcc);
			J(base, base) += (gcc + gee - gce - gec);
			rhs(emitter) -= Ie;
			rhs(collector) -= Ic;
			rhs(base) += Ie + Ic;
		} else {
			int drain = element["drain"]; int source = element["source"]; int gate = element["gate"];
			double v_d = xk_(drain); double v_s = xk_(source); double v_g = xk_(gate);
			double Gds = G_ds(v_g - v_s, v_d - v_s);
			double gm = g_m_MOSFET(v_g - v_s, v_d - v_s);
			double id = i_drain(v_g - v_s, v_d - v_s);
			double Ieq = id - Gds * (v_d - v_s) - gm * (v_g - v_s);
			J(drain, drain) += Gds;
			J(drain, source) -= (Gds + gm);
			J(drain, gate) += gm;
			J(source, drain) -= Gds;
			J(source, source) += (Gds + gm);
			J(source, gate) -= gm;
			J(gate, drain) = 0;
			J(gate, source) = 0;
			J(gate, gate) = 0;
			rhs(drain) -= Ieq;
			rhs(source) += Ieq;
			rhs(gate) = 0;
		}
	}
	MatrixXd J_modified = J(Eigen::lastN(size-1),Eigen::lastN(size-1));
	VectorXd rhs_modified = rhs(Eigen::lastN(size-1));
	return {J_modified, rhs_modified};
}

bool isTerminated(MatrixXd& G, std::vector<Hg>& hg, VectorXd& s, VectorXd& xk1, VectorXd& xk, VectorXd& x0) {
	VectorXd fx = G*xk1 - s;
	for (auto Hg : hg) {
		fx += Hg(xk1);
	}
	return fx.norm() <= TAU_RELATIVE * x0.norm() + TAU_ABSOLUTE && (xk1 - xk).norm() <= TAU_RELATIVE * x0.norm() + TAU_ABSOLUTE;
}


VectorXd newtonMethod(std::list<Element>& nonLinearElements, int numNodes, int numGroup2, MatrixXd& G, std::vector<Hg>& hg, VectorXd& s, VectorXd& xk) {
	/*int size = numNodes + numGroup2 + 1;*/
	VectorXd xk1 = xk;
	VectorXd xk0 = xk;
	while (!isTerminated(G, hg, s, xk1, xk, xk0)) {
		auto [J, rhs] = getJacobianAndRHS(nonLinearElements, numNodes, numGroup2, xk1);
		J += G;
		rhs += s;
		xk = xk1;
		xk1 = solveLinearCircuit(J, rhs);
	}
	return xk1;
}
