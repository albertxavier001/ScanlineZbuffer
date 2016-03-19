#include "Scene.h"


Scene::Scene()
{
	mesh.f.resize(0,0,3);
}


Scene::~Scene()
{
}

void Scene::loadScene(string fileName)
{
	fstream fin(fileName);
	if (!fin.is_open()) {
		cout << "Error: Cannot open file" << endl;
		getchar();
		exit(1);
	}

	string oneline;
	string type;
	while (getline(fin, oneline)) {
		parseLine(oneline);
	}
	
}

void Scene::parseLine(const string &oneline){
	fmat  &v = mesh.v;
	fmat  &n = mesh.n;
	fcube &f = mesh.f;
	
	stringstream ss(oneline);
	string key, val;
	ss >> key;
	
	/// vertex
	if (key == "v") {
		v.resize(3, v.n_cols + 1);
		ss 
			>> v.at(0, v.n_cols - 1)
			>> v.at(1, v.n_cols - 1)
			>> v.at(2, v.n_cols - 1);
	}
	/// normal
	if (key == "vn") {
		n.resize(3, n.n_cols + 1);
		ss
			>> n.at(0, n.n_cols - 1)
			>> n.at(1, n.n_cols - 1)
			>> n.at(2, n.n_cols - 1);
	}
	/// face(temp)
	if (key == "f") {
		int cntSlash = count(ss.str().begin(), ss.str().end(), '/');
		switch (cntSlash) {
		case 0: {
			/// vertex only
			f.resize(3, f.n_cols + 1, f.n_slices);
			/// vertex index
			ss
				>> f.at(0, f.n_cols - 1, 0)
				>> f.at(1, f.n_cols - 1, 0)
				>> f.at(2, f.n_cols - 1, 0);
			break;
		}
		case 3: {break;}
		case 6: {break;}
		default: break;
		}
	}
	/// 

}
