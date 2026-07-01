#include "SlicePhaseTest.h"


void PolygonsPart2VTK (cura::PolygonsPart pp) {
    /*vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    for (int i=0; i<pp.size(); i++) {
	for (int j=0; j<pp[i].size(); j++) {
	    points->InsertNextPoint(pp[i][j].X,pp[i][j].Z,0.0);
	}
    }
    
    vector<vtkSmartPointer<vtkPolygon>> poly;
    */
/*
outer->GetPointIds()->SetNumberOfIds(4);
outer->GetPointIds()->SetId(0, 0);
outer->GetPointIds()->SetId(1, 1);
outer->GetPointIds()->SetId(2, 2);
outer->GetPointIds()->SetId(3, 3);

vtkSmartPointer<vtkPolygon> inner = vtkSmartPointer<vtkPolygon>::New();
inner->GetPointIds()->SetNumberOfIds(4);
inner->GetPointIds()->SetId(0, 4);
inner->GetPointIds()->SetId(1, 5); // 顺时针
inner->GetPointIds()->SetId(2, 6);
inner->GetPointIds()->SetId(3, 7);

// 3. 组装数据集
vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
cells->InsertNextCell(outer);
cells->InsertNextCell(inner);

vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
polyData->SetPoints(points);
polyData->SetPolys(cells);

// 4. Delaunay三角剖分
vtkSmartPointer<vtkDelaunay2D> delaunay = vtkSmartPointer<vtkDelaunay2D>::New();
delaunay->SetInputData(polyData);
delaunay->SetSourceData(polyData);
delaunay->Update();

// 5. 导出VTK文件
vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
writer->SetFileName("result.vtk");
writer->SetInputConnection(delaunay->GetOutputPort());
writer->Write();
*/
}



void Export2VTK (std::string vtkfile, std::vector<std::vector<cura::PolygonsPart>> ppp, cura::Slicer slicer) {
    double scale = 1000;
    
    int n = 0;
    int polynum = 0;
    for(int i=0; i<slicer.layers.size(); i++) {
	for (int j=0; j<ppp[i].size(); j++) {
	    for (int k=0; k<ppp[i][j].size(); k++) {
		n += ppp[i][j][k].size();
		polynum++;
	    }
	}
    }
    std::ofstream out;
    out.open(vtkfile.c_str()); 
    out <<"# vtk DataFile Version 2.0" << std::endl;
    out << "slices example" << std::endl;
    out << "ASCII" << std::endl;
    out << "DATASET POLYDATA" << std::endl;
    out << "POINTS " << n << " float" << std::endl;
    /*
    for(int i=0; i<slicer.layers.size(); i++) {

	for (int j=0; j<layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    for(int k=0; k<sliced_polygon.size(); k++) {
		out << sliced_polygon[k].X / scale << " "
		    << sliced_polygon[k].Y / scale << " "
		    << layer.z / scale << std::endl;
	    }
	}
	}*/
    for(int i=0; i<slicer.layers.size(); i++) {
	const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j=0; j<ppp[i].size(); j++) {
	    for (int k=0; k<ppp[i][j].size(); k++) {
		for (int l=0; l<ppp[i][j][k].size(); l++) {
		    out << ppp[i][j][k][l].X / scale << " "
			<< ppp[i][j][k][l].Y / scale << " "
			<< layer.z / scale << std::endl;
		}
	    }
	}
    }
    
    int m = 0;
    out << "POLYGONS " << polynum << " " << polynum + n  << std::endl;
/*    for(int i = 0; i < slicer.layers.size(); i++) {
	const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j = 0; j < layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    out << sliced_polygon.size();
	    for(int k = 0; k < sliced_polygon.size(); k++) {
		out << " " << m;
		m++;
	    }
	    out << std::endl;
	}
    }
    out.close();
  */
    for(int i=0; i<slicer.layers.size(); i++) {
	for (int j=0; j<ppp[i].size(); j++) {
	    for (int k=0; k<ppp[i][j].size(); k++) {
		out << ppp[i][j][k].size();
		for (int l=0; l<ppp[i][j][k].size(); l++) {
		    out << " " << m;
		    m++;
		}
		out << std::endl;
	    }
	}
    }
    out.close();
}

void Export2VTK (std::string vtkfile, cura::Slicer slicer, const cura::coord_t initial_layer_thickness, const cura::coord_t layer_thickness) {
    double scale = 1000;
    
    int n = 0;
    for(int i=0; i<slicer.layers.size(); i++) {
	const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j=0; j<layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    n += sliced_polygon.size();
	}
    }
    
    //std::cout << n << std::endl;
    //std::cout << cube_mesh.getAABB().min.z << " " << cube_mesh.getAABB().max.z << std::endl;
    //std::cout << cube_mesh.getAABB().min.x << " " << cube_mesh.getAABB().max.x << std::endl;
    //std::cout << cube_mesh.getAABB().min.y << " " << cube_mesh.getAABB().max.y << std::endl;
    
    std::ofstream out;
    out.open(vtkfile.c_str()); 
    out <<"# vtk DataFile Version 2.0" << std::endl;
    out << "slices example" << std::endl;
    out << "ASCII" << std::endl;
    out << "DATASET POLYDATA" << std::endl;
    out << "POINTS " << n << " float" << std::endl;
    for(int i=0; i<slicer.layers.size(); i++) {
	const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j=0; j<layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    for(int k=0; k<sliced_polygon.size(); k++) {
		out << sliced_polygon[k].X / scale << " "
		    << sliced_polygon[k].Y / scale << " "
		    << layer.z / scale << std::endl;
	    }
	}
    }	
    int m = 0;
    out << "POLYGONS " << slicer.layers.size() << " " << slicer.layers.size() + n  << std::endl;
    for(int i = 0; i < slicer.layers.size(); i++) {
	const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j = 0; j < layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    out << sliced_polygon.size();
	    for(int k = 0; k < sliced_polygon.size(); k++) {
		out << " " << m;
		m++;
	    }
	    out << std::endl;
	}
    }
    out.close();
}

void Export2VTK4PathPlanning (std::string vtkfile_pathplanning, cura::Slicer slicer, const cura::coord_t initial_layer_thickness, const cura::coord_t layer_thickness) {
    double scale = 1000;
    
    int n = 0;
    for(int i=1; i<slicer.layers.size(); i++) {
	const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j=0; j<layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    n += sliced_polygon.size();
	}
    }
    
    //std::cout << n << std::endl;
    //std::cout << cube_mesh.getAABB().min.z << " " << cube_mesh.getAABB().max.z << std::endl;
    //std::cout << cube_mesh.getAABB().min.x << " " << cube_mesh.getAABB().max.x << std::endl;
    //std::cout << cube_mesh.getAABB().min.y << " " << cube_mesh.getAABB().max.y << std::endl;
    
    std::ofstream out;
    out.open(vtkfile_pathplanning.c_str());

    out <<"# vtk DataFile Version 2.0" << std::endl;
    out << "slices example" << std::endl;
    out << "ASCII" << std::endl;
    out << "DATASET POLYDATA" << std::endl;
    out << "POINTS " << n << " float" << std::endl;
    for(int i=1; i<slicer.layers.size(); i++) {
        const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j = 0; j < layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    for(int k = 0; k < sliced_polygon.size(); k++) {
	        out << sliced_polygon[k].X / scale << " "
		    << sliced_polygon[k].Y / scale  << " "
		    << layer.z / scale << std::endl;
	    }
	}
    }
    out << "POLYGONS " << slicer.layers.size()-1 << " " << slicer.layers.size()-1 + n << std::endl;
    int m = 0;
    for(int i=1; i<slicer.layers.size(); i++) {
        const cura::SlicerLayer& layer = slicer.layers[i];
	for (int j=0; j<layer.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer.polygons[j];
	    out << sliced_polygon.size();
	    for(int k=0; k<sliced_polygon.size(); k++) {
	        out << " " << m;
		m++;
	    }
	    out << std::endl;
	}
    }
    out.close();
}

void Export2Cli4Mesh (std::string clifile_meshing, cura::Slicer slicer, const cura::coord_t initial_layer_thickness, const cura::coord_t layer_thickness, double buttom) {
    double scale = 1000;
    std::cout << buttom << std::endl;
    std::ofstream out;
    out.open(clifile_meshing.c_str());
    out << "$$HEADERSTART" << std::endl;
    out << "$$ASCII" << std::endl;
    out << "$$UNITS/1" << std::endl;
    out << "$$DATE/230718" << std::endl;
    out << "$$LAYERS/" << slicer.layers.size() + 1<< std::endl;
    out << "$$HEADEREND" << std::endl;
    out << "$$GEOMETRYSTART" << std::endl;

    const cura::SlicerLayer& layer = slicer.layers[0];
    out << "$$LAYER/" << buttom << std::endl;
    for (int j=0; j<layer.polygons.size(); j++) {
	cura::Polygon sliced_polygon = layer.polygons[j];
	out << "$$POLYLINE/0,1," << sliced_polygon.size() + 1;
	for(int k=0; k<sliced_polygon.size(); k++) {
	    out << "," << (sliced_polygon[k].X) / scale << "," << (sliced_polygon[k].Y) / scale;
	}
	out << "," << (sliced_polygon[0].X) / scale << "," << (sliced_polygon[0].Y) / scale
	    << std::endl;
    }
    
    const cura::SlicerLayer& layer1 = slicer.layers[1];
    out << "$$LAYER/" << initial_layer_thickness / scale << std::endl;
    for (int j=0; j<layer1.polygons.size(); j++) {
	cura::Polygon sliced_polygon = layer1.polygons[j];
	out << "$$POLYLINE/0,1," << sliced_polygon.size() + 1;
	for(int k=0; k<sliced_polygon.size(); k++) {
	    out << "," << (sliced_polygon[k].X) / scale << "," << (sliced_polygon[k].Y) / scale;
	}
	out << "," << (sliced_polygon[0].X) / scale << "," << (sliced_polygon[0].Y) / scale
	    << std::endl;
    }

    for(int i=1; i<slicer.layers.size(); i++) {
        const cura::SlicerLayer& layer2 = slicer.layers[i];
	out << "$$LAYER/" << (initial_layer_thickness + i * layer_thickness) / scale << std::endl;
	for (int j=0; j<layer2.polygons.size(); j++) {
	    cura::Polygon sliced_polygon = layer2.polygons[j];
	    out << "$$POLYLINE/0,1," << sliced_polygon.size() + 1;
	    for(int k=0; k<sliced_polygon.size(); k++) {
	        out << "," << (sliced_polygon[k].X) / scale << "," << (sliced_polygon[k].Y) / scale;
	    }
	    out << "," << (sliced_polygon[0].X) / scale << "," << (sliced_polygon[0].Y) / scale
		<< std::endl;
	}
    }
    out << "$$GEOMETRYEND" << std::endl;
    
    out.close();
}
