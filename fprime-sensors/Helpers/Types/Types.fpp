module FprimeSensors {
    @ Struct representing X, Y, Z data
    struct GeometricVector3 {
        x: F32 @< X component of the vector
        y: F32 @< Y component of the vector
        z: F32 @< Z component of the vector
    }
}