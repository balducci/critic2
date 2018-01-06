/*
  Copyright (c) 2017 Alberto Otero de la Roza
  <aoterodelaroza@gmail.com>, Robin Myhr <x@example.com>, Isaac
  Visintainer <x@example.com>, Richard Greaves <x@example.com>, Ángel
  Martín Pendás <angel@fluor.quimica.uniovi.es> and Víctor Luaña
  <victor@fluor.quimica.uniovi.es>.

  critic2 is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at
  your option) any later version.

  critic2 is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <list>
#include <string>

#include "imgui/imgui.h"

#include "tree.h"
#include "critic2.h"

using namespace ImGui;

struct sfield{
  int id;
  std::string name;
};
struct sscene{
  int id;
  std::string name;
  int nf = -1;
  sfield *field = nullptr;
};
struct sfile{
  std::string file;
  std::string path;
  std::list<sscene *> sc = {};
};

static int nsf = 0;
static sfile *sf = nullptr;

void DeleteTreeData(){
  nsf = 0;
  if (sf){
    for (int i=0; i<nsf; i++){
      for (auto it = sf[i].sc.begin(); it != sf[i].sc.end(); it++){
	if ((*it)->field)
	  delete [] (*it)->field;
	delete *it;
      }
      sf[i].sc.clear();
    }
    delete [] sf;
    sf = nullptr;
  }
}

void UpdateTreeData(){
  DeleteTreeData();

  nsf = c2::nfiles;
  sf = new sfile[nsf];

  for (int isc=0; isc<c2::nsc; isc++){
    c2::set_scene_pointers(isc+1);
    int id = c2::idfile-1;
    if (c2::isinit > 0){
      // add the scene to the list of scenes
      sf[id].file = sf[id].path = std::string(c2::file);
      const size_t ll = sf[id].file.find_last_of("\\/");
      if (std::string::npos != ll)
       	sf[id].file.erase(0,ll+1);
      if (std::string::npos != 0)
	sf[id].path.erase(ll+1,std::string::npos);

      // add the scene to the list of scenes
      sscene *sc = new sscene;
      sc->id = isc;
      sc->name = c2::name;

      if (c2::isinit > 1){
	sc->nf = c2::nf;
	char (*fname)[255] = (char (*)[255]) c2::fieldname;
	sc->field = new sfield[sc->nf+1];
	for (int iff = 0; iff <= sc->nf; iff++){
	  sc->field[iff].id = iff;
	  sc->field[iff].name = std::string(fname[iff]);
	}
      } else {
	sc->nf = -1;
	sc->field = nullptr;
      }
      sf[id].sc.push_back(sc);
    }
  }
}

void ShowTree(){
  int n = 0;
  ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow|ImGuiTreeNodeFlags_OpenOnDoubleClick|ImGuiTreeNodeFlags_DefaultOpen;
  for (int i=0; i<nsf; i++){
    n++;
    if (TreeNodeEx((void*)(intptr_t)n,flags,sf[i].file.c_str())){
      for (auto it = sf[i].sc.begin(); it != sf[i].sc.end(); it++){
	n++;
	if (TreeNodeEx((void*)(intptr_t)n,flags,(*it)->name.c_str())){
	  for (int iff=0; iff <= (*it)->nf; iff++){
	    n++;
	    std::string str = std::to_string(iff) + ":" + (*it)->field[iff].name;
	    if (TreeNodeEx((void*)(intptr_t)n,flags|ImGuiTreeNodeFlags_Leaf,str.c_str())){
	      TreePop();
	    }
	  }
	  TreePop();
	}
      }
      TreePop();
    }
  }
}
