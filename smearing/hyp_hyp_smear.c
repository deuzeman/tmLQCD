#include "hyp.ih"

int hyp_smear(gauge_field_t m_field_out, struct hyp_parameters const *params, gauge_field_t m_field_in)
{
  gauge_field_array_t gamma = get_gauge_field_array(3);
  gauge_field_array_t v = get_gauge_field_array(3);

  for (int iter = 0; iter < params->iterations; ++iter)
  {
    /* First level of contractions */
    hyp_staples_exclude_two(gamma, m_field_in);
    APE_project_exclude_two(v, params->alpha[2], gamma, m_field_in);
    for (int idx = 0; idx < 3; ++idx)
      generic_exchange(v.field_array[idx].field, sizeof(su3_tuple));

    /* Second level of contractions */
    hyp_staples_exclude_one(gamma, v);
    APE_project_exclude_one(v, params->alpha[1], gamma, m_field_in);
    for (int idx = 0; idx < 3; ++idx)
      generic_exchange(v.field_array[idx].field, sizeof(su3_tuple));

    /* Final level of contractions  */
    hyp_staples_exclude_none(gamma.field_array[0], v);
    APE_project_exclude_none(m_field_out, params->alpha[0], gamma.field_array[0], m_field_in);
    generic_exchange(m_field_out.field, sizeof(su3_tuple));
    
    m_field_in = m_field_out; /* Prepare for next iteration */
  }

  return_gauge_field_array(&v);
  return_gauge_field_array(&gamma);
  
  return 0;
}

