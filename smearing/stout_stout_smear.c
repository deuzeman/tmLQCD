#include "stout.ih"

#include "stout_smear_plain.static"
#include "stout_smear_with_force_terms.static"

void stout_smear(struct stout_control *control, gauge_field_t in)
{
  control->U[0] = in; /* Shallow copy for convenience */
  
  if (!control->calculate_force_terms)
    stout_smear_plain(control);
  else
    stout_smear_with_force_terms(control);
}
