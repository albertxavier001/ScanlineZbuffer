#include "Zbuffer.h"


Zbuffer::Zbuffer()
{
}


Zbuffer::~Zbuffer()
{
}


QImage Zbuffer::ScanlineZbuffer(
	Scene			&scene, 
	const float		&angleX, 
	const float		&angleY, 
	const float		&scale) 
{
	/// if rotate
	if (angleX != 0.f) 
		scene.cam.rotX(angleX);
	if (angleY != 0.f) 
		scene.cam.rotY(angleY);
	if (scale != 1.f) 
		scene.cam.scale(scale);

	/// create buffer ///xxx???
	vector<float> buffer(scene.cam.w * scene.cam.h, 1.1f);
	QImage image(scene.cam.w, scene.cam.h, QImage::Format_RGB888);
	image.fill(Qt::black);
	for (int i = 0; i < scene.mesh.f.n_cols; i++) {
		scan(scene, i, buffer, image);
	}
	return image;
}

void Zbuffer::scan(
	Scene			&scene, 
	int				_ind, 
	vector<float>	&buffer,
	QImage			&image)
{
	/// face vertex
	
	fmat::fixed<4, 3> v;
	fmat::fixed<4, 3> nm;
	for (int i = 0; i < 3; i++) {
		int ind = scene.mesh.f.slice(0).col(_ind)(i);
		v.col(i) = scene.mesh.v.col(ind);
		nm.col(i) = scene.mesh.n.col(_ind);
	}
	

	fmat::fixed<4, 3> vprj;
	for (int i = 0; i < 3; i++) {
		fvec4 v1 = v.col(i);
		fvec4 v2 = vprj.col(i);
		scene.cam.project(v1, v2);
		vprj.col(i) = v2;
	}
	int ymin, ymax;
	ymin = vprj.row(1).min();
	ymax = vprj.row(1).max();

	vector<vector<Edge> > slNet(ymax-ymin+1);
	initScanLineNewEdgeTable(slNet, v, vprj, nm, ymin, ymax);
	ProcessScanLineFill(slNet, ymin, ymax, image, buffer, scene.light);
}

void Zbuffer::initScanLineNewEdgeTable(
	vector< vector<Edge> >		&slNet,
	fmat::fixed<4, 3>			&v,
	fmat::fixed<4, 3>			&vprj,
	fmat::fixed<4, 3>			&nm,
	int							ymin,
	int							ymax
	)
{
	Edge e;
	
	// for each edge in a face
	for (int i = 0; i < 3; i++)
	{
		const fvec4 &vS = v.col(i);
		const fvec4 &vE = v.col((i + 1) % 3);

		const fvec4 &nS = nm.col(i);
		const fvec4 &nE = nm.col((i + 1) % 3);

		const fvec4 &vprjS = vprj.col(i);
		const fvec4 &vprjE = vprj.col((i + 1) % 3);
		const fvec4 &vprjEE = vprj.col((i + 2) % 3);

		if ((int)vprjE.at(1) == (int)vprjS.at(1))
			continue;

		float fm = (float)(vprjE.at(1) - vprjS.at(1));
		e.dx = (float)(vprjE.at(0) - vprjS.at(0)) 
			/ (float)((int)vprjE.at(1) - (int)vprjS.at(1));
		e.dz = (float)(vprjE.at(2) - vprjS.at(2)) / fm;
		e.dp = (vE - vS) / fm;
		e.dn = (nS - nE) / fm;
		if (vprjE.at(1) > vprjS.at(1))
		{
			e.xi = vprjS.at(0);
			e.zi = vprjS.at(2);
			e.pi = vS;
			e.ni = nS;

			if (vprjEE.at(1) >= vprjE.at(1))
			{
				e.ymax = vprjE.at(1) - 1;
			}
			else
			{
				e.ymax = vprjE.at(1);
			}
			slNet[vprjS.at(1) - ymin].push_back(e);
		}
		else
		{
			e.xi = vprjE.at(0);
			e.zi = vprjE.at(2);
			e.pi = vE;
			e.ni = nE;
			if (vprjEE.at(1) >= vprjS.at(1))
			{
				e.ymax = vprjS.at(1) - 1;
			}
			else
			{
				e.ymax = vprjS.at(1);
			}
			slNet[vprjE.at(1) - ymin].push_back(e);
		}
	}
}


void Zbuffer::ProcessScanLineFill(
	vector<vector<Edge>>		&slNet,
	int							ymin,
	int							ymax,
	QImage						&image,
	vector<float>				&buffer,
	fvec4						&light)
{
	vector<Edge> aet;

	int width = image.width();
	int height = image.height();

	for (int y = ymin; y <= ymax; y++)
	{
		aet.insert(aet.end(), slNet[y - ymin].begin(), slNet[y - ymin].end());
		sort(aet.begin(), aet.end());

		std::vector<Edge>::iterator iter = aet.begin();
		if (y > 0 && y < height) {
			while (iter != aet.end()) {

				int xstart = hp.clamp(iter->xi, 0, width - 1);

				float zi = iter->zi;
				fvec4 pi = iter->pi;
				fvec4 ni = iter->ni;
				if ((iter + 1) == aet.end())	break;
				float dz = (iter + 1)->zi - iter->zi;
				fvec4 dp = (iter + 1)->pi - iter->pi;
				fvec4 dn = (iter + 1)->ni - iter->ni;
				int xend = hp.clamp((++iter)->xi, 0, width - 1);
				dz /= xend - xstart;
				dp /= xend - xstart;
				dn /= xend - xstart;

				for (int x = xstart; x <= xend; x++) {
					if (zi < buffer[y*width + x]) {
						buffer[y*width + x] = zi;
						light.at(3) = 0.f;
						pi.at(3) = 0.f;
						float brdf = fabs(norm_dot((pi - light), ni));
						image.setPixel(x, y, qRgb(250 * brdf, 50 * brdf, 255 * brdf));
					}
					zi += dz;
					pi += dp;
					ni += dn;
				}
				iter++;
			}
		}
		vector<Edge> copyaet = aet;
		aet.clear();
		for (iter = copyaet.begin(); iter != copyaet.end(); iter++) {
			if (iter->ymax != y) {
				iter->xi += iter->dx;
				iter->zi += iter->dz;
				aet.push_back(*iter);
			}
		}
	}
}