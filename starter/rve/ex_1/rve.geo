//+
SetFactory("OpenCASCADE");
Cylinder(1) = {0, 0, 0, 1, 0, 0, 0.2, 2*Pi};

//+
Box(2) = {0, -0.5, -0.5, 1, 1, 1};

BooleanDifference(3) = { Volume{2}; Delete; } { Volume{1}; };
Coherence;

Mesh.CharacteristicLengthMax = 0.1;