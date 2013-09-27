#include <stdarg.h>
#include "goat3d_impl.h"
#include "log.h"

static bool write_material(const Scene *scn, goat3d_io *io, const Material *mat, int level);
static bool write_mesh(const Scene *scn, goat3d_io *io, const Mesh *mesh, int idx, int level);
static bool write_light(const Scene *scn, goat3d_io *io, const Light *light, int level);
static bool write_camera(const Scene *scn, goat3d_io *io, const Camera *cam, int level);
static bool write_node(const Scene *scn, goat3d_io *io, const Node *node, int level);
static void xmlout(goat3d_io *io, int level, const char *fmt, ...);

bool Scene::savexml(goat3d_io *io) const
{
	xmlout(io, 0, "<scene>\n");

	// write environment stuff
	xmlout(io, 1, "<env>\n");
	xmlout(io, 2, "<ambient float3=\"%g %g %g\"/>\n", ambient.x, ambient.y, ambient.z);
	xmlout(io, 1, "</env>\n\n");

	for(size_t i=0; i<materials.size(); i++) {
		write_material(this, io, materials[i], 1);
	}
	for(size_t i=0; i<meshes.size(); i++) {
		write_mesh(this, io, meshes[i], i, 1);
	}
	for(size_t i=0; i<lights.size(); i++) {
		write_light(this, io, lights[i], 1);
	}
	for(size_t i=0; i<cameras.size(); i++) {
		write_camera(this, io, cameras[i], 1);
	}
	for(size_t i=0; i<nodes.size(); i++) {
		write_node(this, io, nodes[i], 1);
	}

	xmlout(io, 0, "</scene>\n");
	return true;
}

static bool write_material(const Scene *scn, goat3d_io *io, const Material *mat, int level)
{
	xmlout(io, level, "<mtl>\n");
	xmlout(io, level + 1, "<name string=\"%s\"/>\n", mat->name.c_str());

	for(int i=0; i<mat->get_attrib_count(); i++) {
		xmlout(io, level + 1, "<attr>\n");
		xmlout(io, level + 2, "<name string=\"%s\"/>\n", mat->get_attrib_name(i));

		const MaterialAttrib &attr = (*mat)[i];
		xmlout(io, level + 2, "<val float4=\"%g %g %g %g\"/>\n", attr.value.x,
				attr.value.y, attr.value.z, attr.value.w);
		if(!attr.map.empty()) {
			xmlout(io, level + 2, "<map string=\"%s\"/>\n", attr.map.c_str());
		}
		xmlout(io, level + 1, "</attr>\n");
	}
	xmlout(io, level, "</mtl>\n\n");
	return true;
}

static bool write_mesh(const Scene *scn, goat3d_io *io, const Mesh *mesh, int idx, int level)
{
	// first write the external (openctm) mesh file
	const char *prefix = scn->get_name();
	if(!prefix) {
		prefix = "goat";
	}

	char *mesh_filename = (char*)alloca(strlen(prefix) + 32);
	sprintf(mesh_filename, "%s-mesh%04d.ctm", prefix, idx);

	if(!mesh->save(mesh_filename)) {
		return false;
	}

	// then refer to that filename in the XML tags
	xmlout(io, level, "<mesh>\n");
	xmlout(io, level + 1, "<name string=\"%s\"/>\n", mesh->name.c_str());
	if(mesh->material) {
		xmlout(io, level + 1, "<material string=\"%s\"/>\n", mesh->material->name.c_str());
	}
	xmlout(io, level + 1, "<file string=\"%s\"/>\n", mesh_filename);
	xmlout(io, level, "</mesh>\n\n");
	return true;
}

static bool write_light(const Scene *scn, goat3d_io *io, const Light *light, int level)
{
	return true;
}

static bool write_camera(const Scene *scn, goat3d_io *io, const Camera *cam, int level)
{
	return true;
}

static bool write_node(const Scene *scn, goat3d_io *io, const Node *node, int level)
{
	return true;
}


static void xmlout(goat3d_io *io, int level, const char *fmt, ...)
{
	for(int i=0; i<level; i++) {
		io_fprintf(io, "  ");
	}

	va_list ap;
	va_start(ap, fmt);
	io_vfprintf(io, fmt, ap);
	va_end(ap);
}