/* Copyright (c) 1997-1999 Miller Puckette and others.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.  */

/* sampling */

/* scale~ from Max/MSP, implemented May 2023 by Orm Finnendahl*/

#include "m_pd.h"
#include "math.h"

#define SCALE_VERSION          "0.1"

/* ------------------------- scale~ -------------------------- */

static t_class *scale_tilde_class;

typedef struct _scale_tilde
{
  t_object x_obj;
  t_float x_in_low;
  t_float x_in_high;
  t_float x_out_low;
  t_float x_out_high;
  t_float x_scaling_curve;
  t_outlet *x_scaleout;
  t_sample x_last_y;
  t_float x_f;
} t_scale_tilde;

static void *scale_tilde_new(t_floatarg min_in, t_floatarg max_in, t_floatarg min_out, t_floatarg max_out, t_floatarg scaling_curve)
{
    t_scale_tilde *x = (t_scale_tilde *)pd_new(scale_tilde_class);
    x->x_in_low = min_in;
    x->x_in_high = max_in;
    x->x_out_low = min_out;
    x->x_out_high = max_out;
    x->x_scaling_curve = scaling_curve;
    outlet_new(&x->x_obj, gensym("signal"));
    floatinlet_new(&x->x_obj, &x->x_in_low);
    floatinlet_new(&x->x_obj, &x->x_in_high);
    floatinlet_new(&x->x_obj, &x->x_out_low);
    floatinlet_new(&x->x_obj, &x->x_out_high);
    floatinlet_new(&x->x_obj, &x->x_scaling_curve);
    return (x);
}



static t_int *scale_tilde_perform(t_int *w)
{
    t_scale_tilde *x = (t_scale_tilde *)(w[1]);
    t_float *in = (t_float *)(w[2]);
    t_float *out = (t_float *)(w[3]);
    int n = (int) w[4];
    while (n--) {
      t_sample f = *in++;
      *out++ = ((x->x_in_high-x->x_in_low) == 0)? 0 :
        ((f - x->x_in_low)/(x->x_in_high - x->x_in_low) == 0) ? x->x_out_low :
        (((f - x->x_in_low)/(x->x_in_high - x->x_in_low)) > 0) ? (x->x_out_low + (x->x_out_high - x->x_out_low) * pow(((f - x->x_in_low)/(x->x_in_high - x->x_in_low)), (x->x_scaling_curve))) :
        ( x->x_out_low + (x->x_out_high - x->x_out_low) * -pow((((x->x_in_low - f)/(x->x_in_high - x->x_in_low))), (float)(x->x_scaling_curve)));
        }
    return (w+5);
}

static void scale_tilde_dsp(t_scale_tilde *x, t_signal **sp)
{
    dsp_add(scale_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, (t_int)sp[0]->s_n);
}

static void scale_tilde_info(t_scale_tilde *x)
{
  post("scale-min-in: %f", x->x_in_low);
  post("scale-max-in: %f", x->x_in_high);
  post("scale-min-out: %f", x->x_out_low);
  post("scale-max-out: %f", x->x_out_high);
  post("scale-scaling-curve: %f", x->x_scaling_curve);
}

void scale_tilde_setup(void)
{
  scale_tilde_class = class_new(gensym("scale~"), (void *) scale_tilde_new, 0,
                                  sizeof(t_scale_tilde), 0, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(scale_tilde_class, t_scale_tilde, x_f);
    class_addmethod(scale_tilde_class, (t_method)scale_tilde_dsp, gensym("dsp"), A_CANT, 0);
    class_addmethod(scale_tilde_class, (t_method)scale_tilde_info, gensym("info"), 0);
}
