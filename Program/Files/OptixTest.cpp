//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <optix.h>
//#include <optix_function_table_definition.h>
//#include <optix_stubs.h>
//#include <cuda_runtime.h>
//#include <cuda_gl_interop.h>
//#include <vector>
//#include <iostream>
//
//// Error checking macros
//#define CUDA_CHECK(call) \
//    { cudaError_t err = call; if (err != cudaSuccess) { std::cerr << "CUDA Error: " << cudaGetErrorString(err) << " at " << __FILE__ << ":" << __LINE__ << std::endl; exit(1); } }
//#define OPTIX_CHECK(call) \
//    { OptixResult res = call; if (res != OPTIX_SUCCESS) { std::cerr << "OptiX Error: " << res << " at " << __FILE__ << ":" << __LINE__ << std::endl; exit(1); } }
//
//// Window dimensions
//const unsigned int WIDTH = 800;
//const unsigned int HEIGHT = 600;
//
//// OpenGL resources
//GLuint pbo;           // Pixel Buffer Object for CUDA-OpenGL interop
//GLuint tex;           // Texture to display OptiX output
//cudaGraphicsResource* cuda_pbo_resource;
//
//// OptiX resources
//OptixDeviceContext optix_context;
//OptixModule module;
//OptixPipeline pipeline;
//OptixProgramGroup raygen_prog_group, miss_prog_group, hitgroup_prog_group;
//OptixShaderBindingTable sbt;
//CUdeviceptr d_output_buffer;
//CUdeviceptr d_sbt_records;
//
//// Camera parameters
//struct Camera {
//    float3 eye = { 0.0f, 0.0f, 3.0f };
//    float3 lookat = { 0.0f, 0.0f, 0.0f };
//    float3 up = { 0.0f, 1.0f, 0.0f };
//    float fov = 60.0f;
//} camera;
//
//// Sphere parameters
//struct Sphere {
//    float3 center = { 0.0f, 0.0f, 0.0f };
//    float radius = 1.0f;
//    float3 color = { 0.8f, 0.3f, 0.2f };
//};
//Sphere sphere;
//CUdeviceptr d_sphere;
//
//// CUDA programs (embedded as strings for simplicity)
//const char* raygen_program = R"(
//#include <optix.h>
//extern "C" __global__ void __raygen__rg() {
//    uint3 idx = optixGetLaunchIndex();
//    uint3 dim = optixGetLaunchDimensions();
//    unsigned int pixel_index = idx.y * dim.x + idx.x;
//
//    // Camera parameters
//    float3 eye = make_float3(0.0f, 0.0f, 3.0f);
//    float aspect = float(dim.x) / float(dim.y);
//    float tan_fov = tanf(radians(60.0f) * 0.5f);
//    float3 u = normalize(make_float3(2.0f * tan_fov * aspect * (float(idx.x) / dim.x - 0.5f), 0.0f, 0.0f));
//    float3 v = normalize(make_float3(0.0f, 2.0f * tan_fov * (0.5f - float(idx.y) / dim.y), 0.0f));
//    float3 w = make_float3(0.0f, 0.0f, -1.0f);
//    float3 direction = normalize(u + v + w);
//
//    // Trace ray
//    float3 payload_rgb = make_float3(0.0f);
//    optixTrace(
//        optixGetPipelineHandle(),
//        eye, direction,
//        0.0f, 1e16f, 0.0f,
//        OptixVisibilityMask(255), OPTIX_RAY_FLAG_NONE,
//        0, 1, 0,
//        (unsigned int*)&payload_rgb.x, (unsigned int*)&payload_rgb.y, (unsigned int*)&payload_rgb.z
//    );
//
//    // Write to output buffer
//    float4* output_buffer = (float4*)optixGetRawBufferPointer(OPTIX_BUFFER_OUTPUT, 0);
//    output_buffer[pixel_index] = make_float4(payload_rgb, 1.0f);
//}
//)";
//
//const char* miss_program = R"(
//#include <optix.h>
//extern "C" __global__ void __miss__ms() {
//    float3* prd = (float3*)optixGetPayloadPointer();
//    prd->x = 0.0f; prd->y = 0.0f; prd->z = 0.0f; // Black background
//}
//)";
//
//const char* closest_hit_program = R"(
//#include <optix.h>
//struct Sphere {
//    float3 center;
//    float radius;
//    float3 color;
//};
//extern "C" __global__ void __closesthit__ch() {
//    float3* prd = (float3*)optixGetPayloadPointer();
//    Sphere* sphere = (Sphere*)optixGetSbtDataPointer();
//    float3 hit_point = optixGetWorldRayOrigin() + optixGetRayTmax() * optixGetWorldRayDirection();
//    float3 normal = normalize(hit_point - sphere->center);
//    float3 light_dir = normalize(make_float3(1.0f, 1.0f, 1.0f));
//    float diffuse = fmaxf(0.0f, dot(normal, light_dir));
//    *prd = sphere->color * diffuse;
//}
//)";
//
//const char* intersection_program = R"(
//#include <optix.h>
//struct Sphere {
//    float3 center;
//    float radius;
//    float3 color;
//};
//extern "C" __global__ void __intersection__sphere() {
//    Sphere* sphere = (Sphere*)optixGetSbtDataPointer();
//    float3 origin = optixGetWorldRayOrigin();
//    float3 direction = optixGetWorldRayDirection();
//    float3 oc = origin - sphere->center;
//    float a = dot(direction, direction);
//    float b = 2.0f * dot(oc, direction);
//    float c = dot(oc, oc) - sphere->radius * sphere->radius;
//    float discriminant = b * b - 4 * a * c;
//    if (discriminant >= 0.0f) {
//        float t = (-b - sqrtf(discriminant)) / (2.0f * a);
//        if (t > 0.0f) {
//            optixReportIntersection(t, 0);
//        }
//    }
//}
//)";
//
//// Initialize OptiX
//void initOptix() {
//    CUDA_CHECK(cudaFree(0)); // Initialize CUDA context
//    OPTIX_CHECK(optixInit());
//
//    // Create OptiX context
//    OptixDeviceContextOptions options = {};
//    options.logCallbackLevel = 4;
//    OPTIX_CHECK(optixDeviceContextCreate(0, &options, &optix_context));
//
//    // Create module
//    OptixModuleCompileOptions module_compile_options = {};
//    OptixPipelineCompileOptions pipeline_compile_options = {};
//    pipeline_compile_options.traversableGraphFlags = OPTIX_TRAVERSABLE_GRAPH_FLAG_ALLOW_SINGLE_GAS;
//    pipeline_compile_options.numPayloadValues = 3;
//    pipeline_compile_options.pipelineLaunchParamsVariableName = "params";
//
//    const char* ptx = nullptr; // In practice, compile CUDA to PTX using nvcc
//    size_t ptx_size = 0;
//    // For simplicity, assume PTX is precompiled (in practice, use CMake to compile CUDA files)
//    // Here, we simulate PTX availability
//    OPTIX_CHECK(optixModuleCreateFromPTX(
//        optix_context, &module_compile_options, &pipeline_compile_options,
//        raygen_program, strlen(raygen_program), nullptr, nullptr, &module
//    ));
//
//    // Create program groups
//    OptixProgramGroupOptions prog_group_options = {};
//    OptixProgramGroupDesc raygen_desc = {};
//    raygen_desc.kind = OPTIX_PROGRAM_GROUP_KIND_RAYGEN;
//    raygen_desc.raygen.module = module;
//    raygen_desc.raygen.entryFunctionName = "__raygen__rg";
//    OPTIX_CHECK(optixProgramGroupCreate(optix_context, &raygen_desc, 1, &prog_group_options, nullptr, nullptr, &raygen_prog_group));
//
//    OptixProgramGroupDesc miss_desc = {};
//    miss_desc.kind = OPTIX_PROGRAM_GROUP_KIND_MISS;
//    miss_desc.miss.module = module;
//    miss_desc.miss.entryFunctionName = "__miss__ms";
//    OPTIX_CHECK(optixProgramGroupCreate(optix_context, &miss_desc, 1, &prog_group_options, nullptr, nullptr, &miss_prog_group));
//
//    OptixProgramGroupDesc hitgroup_desc = {};
//    hitgroup_desc.kind = OPTIX_PROGRAM_GROUP_KIND_HITGROUP;
//    hitgroup_desc.hitgroup.moduleCH = module;
//    hitgroup_desc.hitgroup.entryFunctionNameCH = "__closesthit__ch";
//    hitgroup_desc.hitgroup.moduleIS = module;
//    hitgroup_desc.hitgroup.entryFunctionNameIS = "__intersection__sphere";
//    OPTIX_CHECK(optixProgramGroupCreate(optix_context, &hitgroup_desc, 1, &prog_group_options, nullptr, nullptr, &hitgroup_prog_group));
//
//    // Create pipeline
//    OptixPipelineLinkOptions link_options = {};
//    link_options.maxTraceDepth = 1;
//    std::vector<OptixProgramGroup> program_groups = { raygen_prog_group, miss_prog_group, hitgroup_prog_group };
//    OPTIX_CHECK(optixPipelineCreate(
//        optix_context, &pipeline_compile_options, &link_options,
//        program_groups.data(), program_groups.size(), nullptr, nullptr, &pipeline
//    ));
//
//    // Set up SBT
//    struct RayGenSBT { uint8_t data[OPTIX_SBT_RECORD_HEADER_SIZE]; };
//    struct MissSBT { uint8_t data[OPTIX_SBT_RECORD_HEADER_SIZE]; };
//    struct HitGroupSBT { uint8_t header[OPTIX_SBT_RECORD_HEADER_SIZE]; Sphere sphere; };
//
//    RayGenSBT raygen_record;
//    MissSBT miss_record;
//    HitGroupSBT hitgroup_record;
//    OPTIX_CHECK(optixSbtRecordPackHeader(raygen_prog_group, &raygen_record));
//    OPTIX_CHECK(optixSbtRecordPackHeader(miss_prog_group, &miss_record));
//    OPTIX_CHECK(optixSbtRecordPackHeader(hitgroup_prog_group, &hitgroup_record));
//    hitgroup_record.sphere = sphere;
//
//    std::vector<char> sbt_records;
//    sbt_records.insert(sbt_records.end(), (char*)&raygen_record, (char*)&raygen_record + sizeof(raygen_record));
//    sbt_records.insert(sbt_records.end(), (char*)&miss_record, (char*)&miss_record + sizeof(miss_record));
//    sbt_records.insert(sbt_records.end(), (char*)&hitgroup_record, (char*)&hitgroup_record + sizeof(hitgroup_record));
//
//    CUDA_CHECK(cudaMalloc((void**)&d_sbt_records, sbt_records.size()));
//    CUDA_CHECK(cudaMemcpy((void*)d_sbt_records, sbt_records.data(), sbt_records.size(), cudaMemcpyHostToDevice));
//
//    sbt.raygenRecord = d_sbt_records;
//    sbt.missRecordBase = d_sbt_records + sizeof(raygen_record);
//    sbt.missRecordStrideInBytes = sizeof(miss_record);
//    sbt.missRecordCount = 1;
//    sbt.hitgroupRecordBase = d_sbt_records + sizeof(raygen_record) + sizeof(miss_record);
//    sbt.hitgroupRecordStrideInBytes = sizeof(hitgroup_record);
//    sbt.hitgroupRecordCount = 1;
//
//    // Allocate sphere data
//    CUDA_CHECK(cudaMalloc((void**)&d_sphere, sizeof(Sphere)));
//    CUDA_CHECK(cudaMemcpy((void*)d_sphere, &sphere, sizeof(Sphere), cudaMemcpyHostToDevice));
//}
//
//// Initialize OpenGL
//void initOpenGL() {
//    glewInit();
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//    // Create PBO
//    glGenBuffers(1, &pbo);
//    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
//    glBufferData(GL_PIXEL_UNPACK_BUFFER, WIDTH * HEIGHT * sizeof(float4), nullptr, GL_STREAM_DRAW);
//    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
//
//    // Register PBO with CUDA
//    CUDA_CHECK(cudaGraphicsGLRegisterBuffer(&cuda_pbo_resource, pbo, cudaGraphicsMapFlagsNone));
//
//    // Create texture
//    glGenTextures(1, &tex);
//    glBindTexture(GL_TEXTURE_2D, tex);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//// Render OpenGL
//void render() {
//    // Map PBO to CUDA
//    CUDA_CHECK(cudaGraphicsMapResources(1, &cuda_pbo_resource, 0));
//    CUDA_CHECK(cudaGraphicsResourceGetMappedPointer((void**)&d_output_buffer, nullptr, cuda_pbo_resource));
//
//    // Launch OptiX
//    OPTIX_CHECK(optixLaunch(pipeline, 0, 0, 0, d_output_buffer, WIDTH * HEIGHT * sizeof(float4), &sbt, WIDTH, HEIGHT, 1));
//
//    // Unmap PBO
//    CUDA_CHECK(cudaGraphicsUnmapResources(1, &cuda_pbo_resource, 0));
//
//    // Render quad with texture
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBindTexture(GL_TEXTURE_2D, tex);
//    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
//    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGBA, GL_FLOAT, nullptr);
//    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
//
//    glEnable(GL_TEXTURE_2D);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
//    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
//    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
//    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
//    glEnd();
//    glDisable(GL_TEXTURE_2D);
//
//    glutSwapBuffers();
//}
//
//// GLUT display callback
//void display() {
//    render();
//    glutPostRedisplay();
//}
//
//// Cleanup
//void cleanup() {
//    CUDA_CHECK(cudaGraphicsUnregisterResource(cuda_pbo_resource));
//    CUDA_CHECK(cudaFree(d_output_buffer));
//    CUDA_CHECK(cudaFree(d_sbt_records));
//    CUDA_CHECK(cudaFree(d_sphere));
//    OPTIX_CHECK(optixPipelineDestroy(pipeline));
//    OPTIX_CHECK(optixProgramGroupDestroy(raygen_prog_group));
//    OPTIX_CHECK(optixProgramGroupDestroy(miss_prog_group));
//    OPTIX_CHECK(optixProgramGroupDestroy(hitgroup_prog_group));
//    OPTIX_CHECK(optixModuleDestroy(module));
//    OPTIX_CHECK(optixDeviceContextDestroy(optix_context));
//    glDeleteBuffers(1, &pbo);
//    glDeleteTextures(1, &tex);
//}
//
//// GLUT keyboard callback
//void keyboard(unsigned char key, int x, int y) {
//    if (key == 27) { // ESC key
//        cleanup();
//        glutDestroyWindow(glutGetWindow());
//        exit(0);
//    }
//}
//
//int main(int argc, char* argv[]) {
//    // Initialize GLUT
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//    glutInitWindowSize(WIDTH, HEIGHT);
//    glutCreateWindow("OptiX Sphere in OpenGL");
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//
//    // Initialize OpenGL and OptiX
//    initOpenGL();
//    initOptix();
//
//    // Start rendering loop
//    glutMainLoop();
//    return 0;
//}