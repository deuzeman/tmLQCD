#include "hyp.ih"

void hyp_staples_exclude_none(gauge_field_t buff_out, gauge_field_array_t buff_in)
{
  static su3 tmp;
  memset(buff_out.field, 0, sizeof(su3_tuple) * VOLUMEPLUSRAND); /* Brutal but fast zeroing of buffer... */

#define _ADD_STAPLES_TO_COMPONENT(component, to, via, x) \
  { \
    _su3_times_su3d(tmp, buff_in.field_array[I1_ ## to ## _ ## via / 4].field[g_iup[x][via]][I1_ ## to ## _ ## via % 4], buff_in.field_array[I1_ ## via ## _ ## to / 4].field[g_iup[x][to]][I1_ ## via ## _ ## to % 4]); \
    _su3_times_su3_acc(buff_out.field[x][component], buff_in.field_array[I1_ ## via ## _ ## to / 4].field[x][I1_ ## via ## _ ## to % 4], tmp); \
    _su3_times_su3(tmp, buff_in.field_array[I1_ ## to ## _ ## via / 4].field[g_idn[x][via]][I1_ ## to ## _ ## via % 4], buff_in.field_array[I1_ ## via ## _ ## to / 4].field[g_iup[g_idn[x][via]][to]][I1_ ## via ## _ ## to % 4]); \
    _su3d_times_su3_acc(buff_out.field[x][component], buff_in.field_array[I1_ ## via ## _ ## to / 4].field[g_idn[x][via]][I1_ ## via ## _ ## to % 4], tmp); \
  }

  for (int x = 0; x < VOLUME; ++x)
  {
    _ADD_STAPLES_TO_COMPONENT(I0_0, 0, 1, x);
    _ADD_STAPLES_TO_COMPONENT(I0_0, 0, 2, x);
    _ADD_STAPLES_TO_COMPONENT(I0_0, 0, 3, x);

    _ADD_STAPLES_TO_COMPONENT(I0_1, 1, 0, x);
    _ADD_STAPLES_TO_COMPONENT(I0_1, 1, 2, x);
    _ADD_STAPLES_TO_COMPONENT(I0_1, 1, 3, x);

    _ADD_STAPLES_TO_COMPONENT(I0_2, 2, 0, x);
    _ADD_STAPLES_TO_COMPONENT(I0_2, 2, 1, x);
    _ADD_STAPLES_TO_COMPONENT(I0_2, 2, 3, x);

    _ADD_STAPLES_TO_COMPONENT(I0_3, 3, 0, x);
    _ADD_STAPLES_TO_COMPONENT(I0_3, 3, 1, x);
    _ADD_STAPLES_TO_COMPONENT(I0_3, 3, 2, x);
  }

#undef _ADD_STAPLES_TO_COMPONENT
}
