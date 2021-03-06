#ifndef GUARD_SMEARING_IDENTITY_H
#define GUARD_SMEARING_IDENTITY_H

#include <buffers/adjoint.h>
#include <buffers/gauge.h>
#include <buffers/utils.h>

typedef struct
{ 
  /* Flags */
  /* FIXME The generic structor of control structs currently requires these flags... */
  int smearing_performed;
  
  /* Results -- main output for users */
  gauge_field_t    result; /* For direct access to the result, shallow copy... */
  adjoint_field_t  force_result; /* In this particular case, also a shallow copy... */
} identity_control;

identity_control *construct_identity_control(int calculate_force_terms);
static inline void free_identity_control(identity_control *control);

static inline void identity_smear(identity_control *control, gauge_field_t in);
static inline void identity_smear_forces(identity_control *control, adjoint_field_t in);

#include "identity.inlines"

#endif
