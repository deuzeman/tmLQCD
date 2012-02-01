#include "stout.ih"

void stout_smear(gauge_field_t m_field_out, struct stout_parameters const *params, gauge_field_t m_field_in)
{
  gauge_field_t buffer = get_gauge_field();
  
  for(int iter = 0; iter < params->iterations; ++iter)
  {
    generic_staples(buffer, m_field_in);
    stout_links(buffer, params->rho, buffer, m_field_in);
    copy_gauge_field(m_field_out, buffer);
    exchange_gauge_field(m_field_out);

    m_field_in = m_field_out; /* Prepare for next iteration */
  }
  
  return_gauge_field(&buffer);
}
