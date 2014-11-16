#include "EdgeThicknessParameter.h"
#include <cassert>

void EdgeThicknessParameter::apply(VectorF& results,
        const PatternParameter::Variables& vars) {
    const size_t num_edges = m_wire_network->get_num_edges();
    const size_t roi_size = m_roi.size();

    assert(results.size() == num_edges);

    if (m_formula != "") evaluate_formula(vars);

    for (size_t i=0; i<roi_size; i++) {
        assert(m_roi[i] < num_edges);
        results[m_roi[i]] = m_value;
    }
}
