/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */

#include <subdev/mc.h>

struct nv98_mc_priv {
	struct nouveau_mc base;
};

static const struct nouveau_mc_intr
nv98_mc_intr[] = {
	{ 0x00000001, NVDEV_ENGINE_PPP },
	{ 0x00000100, NVDEV_ENGINE_FIFO },
	{ 0x00001000, NVDEV_ENGINE_GR },
	{ 0x00004000, NVDEV_ENGINE_CRYPT },	/* NV84:NVA3 */
	{ 0x00008000, NVDEV_ENGINE_BSP },
	{ 0x00080000, NVDEV_SUBDEV_THERM },	/* NVA3:NVC0 */
	{ 0x00100000, NVDEV_SUBDEV_TIMER },
	{ 0x00200000, NVDEV_SUBDEV_GPIO },
	{ 0x00400000, NVDEV_ENGINE_COPY0 },	/* NVA3-     */
	{ 0x04000000, NVDEV_ENGINE_DISP },
	{ 0x10000000, NVDEV_SUBDEV_BUS },
	{ 0x80000000, NVDEV_ENGINE_SW },
	{ 0x0040d101, NVDEV_SUBDEV_FB },
	{},
};

static int
nv98_mc_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	     struct nouveau_oclass *oclass, void *data, u32 size,
	     struct nouveau_object **pobject)
{
	struct nv98_mc_priv *priv;
	int ret;

	ret = nouveau_mc_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	nv_subdev(priv)->intr = nouveau_mc_intr;
	priv->base.intr_map = nv98_mc_intr;
	return 0;
}

struct nouveau_oclass
nv98_mc_oclass = {
	.handle = NV_SUBDEV(MC, 0x98),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv98_mc_ctor,
		.dtor = _nouveau_mc_dtor,
		.init = nv50_mc_init,
		.fini = _nouveau_mc_fini,
	},
};
