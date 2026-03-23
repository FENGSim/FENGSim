#Write a Julia script using Gmsh to create three spheres:
#one large sphere centered at (0, 0, 0) with radius 1,
#and two small spheres centered at (0.2, 0, 0) and (-0.2, 0, 0) respectively, each with radius 0.1.
#Then, subtract the two small spheres from the large sphere and generate the mesh.

using Gmsh

function create_spheres_with_cavities()
    # Initialize Gmsh
    gmsh.initialize()
    gmsh.model.add("spheres_with_cavities")
    
    # Define sphere parameters
    # Large sphere: center at (0, 0, 0), radius = 1
    big_center = [0.0, 0.0, 0.0]
    big_radius = 1.0
    
    # Small sphere 1: center at (0.2, 0, 0), radius = 0.1
    small1_center = [0.2, 0.0, 0.0]
    small_radius = 0.1
    
    # Small sphere 2: center at (-0.2, 0, 0), radius = 0.1
    small2_center = [-0.2, 0.0, 0.0]
    
    # Create the large sphere
    big_sphere = gmsh.model.occ.addSphere(
        big_center[1], big_center[2], big_center[3], 
        big_radius
    )
    
    # Create the two small spheres
    small_sphere1 = gmsh.model.occ.addSphere(
        small1_center[1], small1_center[2], small1_center[3], 
        small_radius
    )
    
    small_sphere2 = gmsh.model.occ.addSphere(
        small2_center[1], small2_center[2], small2_center[3], 
        small_radius
    )
    
    # Perform Boolean subtraction: large sphere minus the two small spheres
    # First subtraction: large sphere - small sphere 1
    cut1, _ = gmsh.model.occ.cut(
        [(3, big_sphere)],      # Object to cut from
        [(3, small_sphere1)]     # Tool to subtract
    )
    
    # Second subtraction: result from first cut minus small sphere 2
    final_volume, _ = gmsh.model.occ.cut(
        [cut1[1]],               # Result from first cut
        [(3, small_sphere2)]     # Second tool to subtract
    )
    
    # Synchronize the OpenCASCADE model with the Gmsh model
    gmsh.model.occ.synchronize()
    
    # Set mesh parameters
    # Global mesh size control
    gmsh.option.setNumber("Mesh.CharacteristicLengthMin", 0.03)
    gmsh.option.setNumber("Mesh.CharacteristicLengthMax", 0.1)
    
    # Refine mesh near the small spheres (optional)
    # Get all surfaces
    surfaces = gmsh.model.getEntities(2)
    
    for (dim, tag) in surfaces
        # Get bounding box of each surface
        (xmin, ymin, zmin, xmax, ymax, zmax) = gmsh.model.getBoundingBox(dim, tag)
        center = [(xmin + xmax)/2, (ymin + ymax)/2, (zmin + zmax)/2]
        
        # Check if surface belongs to small sphere cavities
        # Distance from center to small sphere centers
        dist_to_small1 = sqrt((center[1] - small1_center[1])^2 + 
                              (center[2] - small1_center[2])^2 + 
                              (center[3] - small1_center[3])^2)
        dist_to_small2 = sqrt((center[2] - small2_center[2])^2 + 
                              (center[2] - small2_center[2])^2 + 
                              (center[3] - small2_center[3])^2)
        
        # Refine mesh on cavity surfaces
        if abs(dist_to_small1 - small_radius) < 0.05 || 
           abs(dist_to_small2 - small_radius) < 0.05
            gmsh.model.mesh.setSize([(dim, tag)], 0.02)
        end
    end
    
    # Set mesh algorithm
    gmsh.option.setNumber("Mesh.Algorithm3D", 4)  # Delaunay 3D algorithm
    
    # Generate 3D mesh
    println("Generating 3D mesh...")
    gmsh.model.mesh.generate(3)
    
    # Save the mesh to file
    output_file = "spheres_with_cavities.msh"
    gmsh.write(output_file)
    println("Mesh saved to: ", output_file)
    
    # Optional: Launch GUI to view the mesh
    # Uncomment the following line to open the Gmsh GUI
    # gmsh.fltk.run()
    
    # Clean up
    gmsh.finalize()
    
    println("Done! Created a large sphere with two spherical cavities.")
    println("  - Large sphere radius: 1.0 at origin")
    println("  - Small sphere 1: radius 0.1 at (0.2, 0, 0)")
    println("  - Small sphere 2: radius 0.1 at (-0.2, 0, 0)")
end

# Run the script
create_spheres_with_cavities()
