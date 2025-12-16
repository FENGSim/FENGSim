SetFactory("OpenCASCADE");

Merge "a.step";
//Sphere(1) = {0,0,0,1};
Box(2) = {-2,-2,-2,4,4,4};
BooleanDifference(3) = { Volume{2}; Delete; } { Volume{1}; };
Coherence;
