#ifndef CHUNK_H_
#define CHUNK_H_

#include <stdint.h>

enum {
	CNK_INVALID,		// this shouldn't appear in files
	CNK_SCENE,			// the root chunk

	// general purpose chunks
	CNK_INT,
	CNK_INT4,
	CNK_FLOAT,
	CNK_FLOAT3,
	CNK_FLOAT4,
	CNK_STRING,

	// --- first level chunks ---
	// children of CNK_SCENE
	CNK_ENV,			// environmental parameters
	CNK_MTL_LIST,		// material library
	CNK_MESH_LIST,		// all the meshes hang under this chunk
	CNK_LIGHT_LIST,		// likewise for lights
	CNK_CAMERA_LIST,	// likewise for cameras
	CNK_NODE_LIST,		// likewise for nodes

	// --- second level chunks ---
	// children of CNK_ENV
	CNK_ENV_AMBIENT,	// ambient color, contains a single CNK_FLOAT3
	CNK_ENV_FOG,

	// children of CNK_*_LIST
	CNK_MTL,
	CNK_MESH,
	CNK_LIGHT,
	CNK_CAMERA,
	CNK_NODE,

	// --- third level chunks ---
	// children of CNK_FOG
	CNK_FOG_COLOR,		// fog color, contains a single CNK_FLOAT3
	CNK_FOG_EXP,		// fog exponent, contains a single CNK_REAL

	// children of CNK_MTL
	CNK_MTL_ATTR,		// material attribute, has a CNK_STRING for its name,
						// a CNK_MTL_ATTR_VAL, and optionally a CNK_MTL_ATTR_MAP
	// children of CNK_MTL_ATTR
	CNK_MTL_ATTR_VAL,	// can have a single CNK_FLOAT, CNK_FLOAT3, or CNK_FLOAT4
	CNK_MTL_ATTR_MAP,	// has a single CNK_STRING

	// children of CNK_MESH
	CNK_MESH_NAME,			// has a single CNK_STRING
	CNK_MESH_MATERIAL,		// has one of CNK_STRING or CNK_INT to identify the material
	CNK_MESH_VERTEX_LIST,	// has a series of CNK_FLOAT3 chunks
	CNK_MESH_NORMAL_LIST,	// has a series of CNK_FLOAT3 chunks
	CNK_MESH_TANGENT_LIST,	// has a series of CNK_FLOAT3 chunks
	CNK_MESH_TEXCOORD_LIST,	// has a series of CNK_FLOAT3 chunks
	CNK_MESH_SKINWEIGHT_LIST,	// has a series of CNK_FLOAT4 chunks (4 skin weights)
	CNK_MESH_SKINMATRIX_LIST,	// has a series of CNK_INT4 chunks (4 matrix indices)
	CNK_MESH_COLOR_LIST,	// has a series of CNK_FLOAT4 chunks
	CNK_MESH_BONES_LIST,	// has a series of CNK_INT or CNK_STRING chunks identifying the bone nodes
	CNK_MESH_FACE_LIST,		// has a series of CNK_FACE chunks

	// child of CNK_MESH_FACE_LIST
	CNK_MESH_FACE,			// has three CNK_INT chunks

	// children of CNK_LIGHT
	CNK_LIGHT_NAME,			// has a single CNK_STRING
	CNK_LIGHT_POS,			// has a single CNK_FLOAT3
	CNK_LIGHT_COLOR,		// has a single CNK_FLOAT3
	CNK_LIGHT_ATTEN,		// has a single CNK_FLOAT3 (constant, linear, squared attenuation)
	CNK_LIGHT_DISTANCE,		// has a single CNK_FLOAT
	CNK_LIGHT_DIR,			// a single CNK_FLOAT3 (for spotlights and dir-lights)
	CNK_LIGHT_CONE_INNER,	// single CNK_FLOAT, inner cone angle (for spotlights)
	CNK_LIGHT_CONE_OUTER,	// single CNK_FLOAT, outer cone angle (for spotlights)

	// children of CNK_CAMERA
	CNK_CAMERA_NAME,		// has a single CNK_STRING
	CNK_CAMERA_POS,			// single CNK_FLOAT3
	CNK_CAMERA_TARGET,		// single CNK_FLOAT3
	CNK_CAMERA_FOV,			// single CNK_FLOAT (field of view in radians)
	CNK_CAMERA_NEARCLIP,	// single CNK_FLOAT (near clipping plane distance)
	CNK_CAMERA_FARCLIP,		// signle CNK_FLOAT (far clipping plane distance)

	// children of CNK_NODE
	CNK_NODE_NAME,			// node name, a single CNK_STRING
	CNK_NODE_PARENT,		// it can have a CNK_INT or a CNK_STRING to identify the parent node

	CNK_NODE_MESH,			// it can have a CNK_INT or a CNK_STRING to identify this node's mesh
	CNK_NODE_LIGHT,			// same as CNK_NODE_MESH
	CNK_NODE_CAMERA,		// same as CNK_NODE_MESH

	CNK_NODE_POS,			// has a CNK_VEC3, position vector
	CNK_NODE_ROT,			// has a CNK_VEC4, rotation quaternion (x, y, z imaginary, w real)
	CNK_NODE_SCALE,			// has a CNK_VEC3, scaling
	CNK_NODE_PIVOT,			// has a CNK_VEC3, pivot point

	CNK_NODE_MATRIX0,		// has a CNK_VEC4, first matrix row (4x3)
	CNK_NODE_MATRXI1,		// has a CNK_VEC4, second matrix row (4x3)
	CNK_NODE_MATRIX2,		// has a CNK_VEC4, third matrix row (4x3)

	MAX_NUM_CHUNKS
};

#define UNKNOWN_SIZE	((uint32_t)0xbaadf00d)

struct ChunkHeader {
	uint32_t id;
	uint32_t size;
};

struct Chunk {
	ChunkHeader hdr;
	char data[1];
};



#endif	// CHUNK_H_