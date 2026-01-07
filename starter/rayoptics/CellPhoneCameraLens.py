import matplotlib.pyplot as plt
plt.ion()
isdark = False

# use standard rayoptics environment
from rayoptics.environment import *

# util functions
from rayoptics.util.misc_math import normalize

opm = OpticalModel()
sm = opm['seq_model']
osp = opm['optical_spec']
pm = opm['parax_model']
em = opm['ele_model']
pt = opm['part_tree']

opm.system_spec.title = 'Cell Phone Lens - U.S. Patent 7,535,658'
opm.system_spec.dimensions = 'mm'

osp['pupil'] = PupilSpec(osp, key=['image', 'f/#'], value=3.5)
osp['fov'] = FieldSpec(osp, key=['image', 'height'], value=3.5, is_relative=True, flds=[0., .7071, 1])
osp['wvls'] = WvlSpec([('F', 0.5), ('d', 1.0), ('C', 0.5)], ref_wl=1)

opm.radius_mode = True

sm.gaps[0].thi=1e10

sm.add_surface([0., 0.])
sm.set_stop()

sm.add_surface([1.962, 1.19, 1.471, 76.6])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=1.962, ec=2.153,
                        coefs=[0., 0., -1.895e-2, 2.426e-2, -5.123e-2, 8.371e-4, 7.850e-3, 4.091e-3, -7.732e-3, -4.265e-3])

sm.add_surface([33.398, .93])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=33.398, ec=40.18,
                        coefs=[0., 0., -4.966e-3, -1.434e-2, -6.139e-3, -9.284e-5, 6.438e-3, -5.72e-3, -2.385e-2, 1.108e-2])

sm.add_surface([-2.182, .75, 1.603, 27.5])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=-2.182, ec=2.105,
                        coefs=[0., 0., -4.388e-2, -2.555e-2, 5.16e-2, -4.307e-2, -2.831e-2, 3.162e-2, 4.630e-2, -4.877e-2])

sm.add_surface([-6.367, 0.1])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=-6.367, ec=3.382,
                        coefs=[0., 0., -1.131e-1, -7.863e-2, 1.094e-1, 6.228e-3, -2.216e-2, -5.89e-3, 4.123e-3, 1.041e-3])

sm.add_surface([5.694, .89, 1.510, 56.2])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=5.694, ec=-221.1,
                        coefs=[0., 0., -7.876e-2, 7.02e-2, 1.575e-3, -9.958e-3, -7.322e-3, 6.914e-4, 2.54e-3, -7.65e-4])

sm.add_surface([9.192, .16])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=9.192, ec=0.9331,
                        coefs=[0., 0., 9.694e-3, -2.516e-3, -3.606e-3, -2.497e-4, -6.84e-4, -1.414e-4, 2.932e-4, -7.284e-5])

sm.add_surface([1.674, .85, 1.510, 56.2])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=1.674, ec=-7.617,
                        coefs=[0., 0., 7.429e-2, -6.933e-2, -5.811e-3, 2.396e-3, 2.100e-3, -3.119e-4, -5.552e-5, 7.969e-6])

sm.add_surface([1.509, .70])
sm.ifcs[sm.cur_surface].profile = RadialPolynomial(r=1.509, ec=-2.707,
                        coefs=[0., 0., 1.767e-3, -4.652e-2, 1.625e-2, -3.522e-3, -7.106e-4, 3.825e-4, 6.271e-5, -2.631e-5])

sm.add_surface([0., .40, 1.516, 64.1])
sm.add_surface([0., .64])

opm.update_model()

sm.do_apertures = False

sm.list_model()

pm.first_order_data()

pt.list_model()

layout_plt0 = plt.figure(FigureClass=InteractiveLayout, opt_model=opm,
                        do_draw_rays=True, do_paraxial_layout=False,
                        is_dark=isdark).plot()

plt.show(block=True)
