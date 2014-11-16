#include "VertexThicknessParameter.h"
#include <cassert>

void VertexThicknessParameter::apply(VectorF& results,
        const PatternParameter::Variables& vars) {
    const size_t num_vertices = m_wire_network->get_num_vertices();
    const size_t roi_size = m_roi.size();
    assert(results.size() == num_vertices);

    if (m_formula != "") evaluate_formula(vars);

    for (size_t i=0; i<roi_size; i++) {
        assert(m_roi[i] < num_vertices);
        results[m_roi[i]] = m_value;
    }
}
