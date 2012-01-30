#pragma once

#include <buffers/adjoint.h>
#include <buffers/gauge.h>

void generic_exchange(void *field_in, int bytes_per_site);

void copy_gauge_field(gauge_field_t dest, gauge_field_t orig);
void copy_adjoint_field(adjoint_field_t dest, adjoint_field_t orig);

void exchange_gauge_field(gauge_field_t target);
void exchange_gauge_field_array(gauge_field_array_t target);

void exchange_adjoint_field(adjoint_field_t target);
void exchange_adjoint_field_array(adjoint_field_array_t target);

/* Inline functions need to be declared inside the header -- hence the following nastiness here... */

#define __DEFINE_BUFFER_INLINES(DATATYPE, NAME)							\
inline void copy_ ## NAME ## _field(NAME ## _field_t dest,  NAME ## _field_t orig)       \
{                                                                                               \
  memmove((void*)dest.field, (void*)orig.field, sizeof(DATATYPE) * VOLUMEPLUSRAND + 1);         \
}												\
                                                                                                \
inline void exchange_ ## NAME ## _field(NAME ## _field_t target)                            \
{                                                                                               \
  generic_exchange((void*)target.field, sizeof(DATATYPE));                                      \
}                                                                                               \
                                                                                                \
inline void exchange_ ## NAME ## _field_array(NAME ## _field_array_t target)                \
{                                                                                               \
  for (unsigned int idx = 0; idx < target.length; ++idx)                                        \
    exchange_ ## NAME ## _field(target.field_array[idx]);                                       \
}

__DEFINE_BUFFER_INLINES(su3_tuple, gauge)
__DEFINE_BUFFER_INLINES(su3adj_tuple, adjoint)

#undef __DEFINE_BUFFER_INLINES