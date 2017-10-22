# define TRUE 1
# define FALSE 0
# define INFIN 1e20f
# define EPS 0.0001f

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3
# define PARABOLOID 4
# define TORUS 5
# define DISK 6
# define TRIANGLE 7
# define CUBE 8
# define BOX 9
# define BOCAL 10
# define MOEBIUS 11
# define ELIPSOID 12
# define DNA 13
# define HEART 14
# define CUBEHOLE 15
# define TETRAHEDRON 16
# define STAR 17
# define OCTAHEDRON 18
# define CUBOHEDRON 19
# define RING 20

# define DIFF 0
# define SPEC 1
# define REFR 2
# define GLOSSY 3
# define GLOSSY_REFR 4
# define TRANSPARENT 5
# define NEGATIVE 6

# define TRUE_CHECKER -5
# define CHECKERBOARD -4
# define PERLIN -3
# define NORMAL -2

# define STANDARD 0
# define UNCHARTED 1
# define STRONG 2

# define SEPIA 1
# define GREYSCALE 2
# define FOG 3

# define DOF 1
# define FISHEYE 2

# define MY_PI 3.141593f
# define TWO_PI 2 * MY_PI
# define I_MY_PI 1 / MY_PI
# define RAD MY_PI / 180.0f
# define TO_RAD(a) (a * RAD)

typedef struct s_state
{
	float3		rad;
	float3		path_capacity;
	float3		current_absorption;
	int			specular_bounce;
	int			glossy_bounce;
	int			through_transparent;
	int			is_survive;
}				t_state;

typedef struct	s_camera
{
	float3		pos;
	float3		dir;
	float3		right;
	float3		up;
	float		fov;
	float		aspectratio;
	float		angle;
	float		inv_width;
	float		inv_height;
	float		aperture;
	float		focal_length;
	float		t;
}				t_camera;

typedef struct		s_moebius
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
}					t_moebius;

typedef struct		s_complex
{
	double		Re;
	double		Im;
}					t_complex;

typedef struct	s_quad
{
	float		t0;
	float		t1;
	float3		x;
	float		a;
	float		b;
	float		c;
	float		d;
	float		t2;
	float		m;
	float		dd;
}				t_quad;

typedef struct	s_quaternion
{
	float		w;
	float3		v;
}				t_quaternion;

typedef struct	s_basis
{
	float3		w;
	float3		u;
	float3		v;
}				t_basis;

typedef struct	s_ray
{
	float3		d;
	float3		o;
	float		t;
}				t_ray;

typedef struct	s_scene
{
	float3		ambient;
	float3		parallel_dir;
	float3		parallel_emis;
	int			image_width;
	int			image_height;
	int			amount_of_objects;
	int			amount_of_spotlights;
	int			amount_of_albedo_textures;
	int			amount_of_negative_objects;
	int			env_map_w;
	int			env_map_h;
	float		max_distance;
	float		gamma;
	char		light_on;
	char		parallel_light;
	char		indirect_light;
	char		spotlight;
	char		visual_effect;
	char		amount_of_nodes;
	char		node_id;
	char		mode;
	char		env_map;
	char		radiance_env_map;
	char		tone_mapper;
	char		dummy[9];
}				t_scene;

typedef struct	s_spotlight
{
	float3		pos;
	float3		dir;
	float3		emission;
	float3		u;
	float3		v;
	float3		w;
	float		alpha;
	float		radius;
}				t_spotlight;

typedef struct	s_object
{
	float3		emission;
	float3		dir;
	float3		point1;
	float3		point2;
	float3		point3;
	float3		n;
	float3		edge0;
	float3		edge1;
	float3		edge2;
	float3		color;
	float3		absorption;
	float3		upsilon;
	float3		a;
	float3		b;
	float3		c;
	float		tex_scale;
	float		radius;
	float		radius2;
	float		bot;
	float		top;
	float		k;
	float		c2;
	float		glossiness;
	float		kd;
	float		refr_index;
	float		tex_shift;
	float		dummy1;
	int			period;
	int			frequency;
	int			type;
	int			material;
	int			albedo_n;
	int			dummy2;
	int			dummy3;
	int			dummy4;
}				t_object;

typedef struct	s_intersection
{
	float3		hit_point;
	float3		normal;
	float3		radiance;
	float3		u;
	float3		v;
	float3		color;
	int			took_place;
	int			negative;
}				t_intersection;

typedef struct	s_negative
{
	float3		hit_point;
	float3		normal;
	float2		range;
}				t_negative;

typedef struct	s_matrix
{
	float3		a;
	float3		b;
	float3		c;
}				t_matrix;


typedef struct	s_kernel_prim_ray
{
	t_camera	camera;
	t_scene		scene;
	t_ray		ray;
}				t_kernel_prim_ray;

typedef struct	s_kernel_intersection
{
	t_state		state;
	t_scene		scene;
	t_object	object;
}				t_kernel_intersection;

typedef struct	s_kernel_rad
{
	t_intersection	issect;
	t_scene			scene;
	t_object		object;
}				t_kernel_rad;

typedef struct	s_kernel_trace
{
	t_state			state;
	t_intersection	issect;
	t_scene			scene;
	t_object		object;
	t_ray			ray;
}				t_kernel_trace;

typedef struct	s_kernel_images
{
	t_scene			scene;
	float3			color;
	t_state			state;
}				t_kernel_image;

int				my_sgn(double x);
t_quaternion	init_quat(float3 v, float w);
void			normalise_quat(t_quaternion *q);
t_quaternion	invert_quat(t_quaternion q);
t_quaternion	quat_mult_quat(t_quaternion q1, t_quaternion q2);
t_quaternion	quat_mult_3(t_quaternion q, float3 v);
float3			quat_transform_vec3(t_quaternion q, float3 v);
t_complex		sqrt_complex(t_complex c);

t_basis			get_basis_from_vec(float3 dir);
float			intersect(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n);
float			intersect_sphere(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n);
float			intersect_plane(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n);
float			intersect_cylinder(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n);
float			intersect_paraboloid(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n);
float			intersect_cube(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n);
float			intersect_cubehole(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_tetrahedron(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_octahedron(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_cubohedron(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_star(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_cone(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_elipsoid(t_object obj, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_triangle(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_disk(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_box(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_bocal(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_torus(t_object obj, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_moebius(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_dna(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_heart(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
float			intersect_ring(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp);
int				intersect_in_range(__constant t_object *objects, __constant t_scene *scene, t_ray r, const float maxt, t_intersection issect, float3 *path_capacity, __global float3 *albedo_textures, int k, __global float *perlin, t_negative negative);
int				solve_quadratic(t_quad *q);
void			float_swap(float *a, float *b);
bool			check_for_m_cyl(t_ray ray, t_object object, t_quad q, float t);
bool			check_for_m_cone(t_ray ray, t_object object, t_quad q, float t);
float			get_random(unsigned int *seed0, unsigned int *seed1);
float3			get_direct_light(__constant t_object *objects, __constant t_scene *scene, unsigned int *seed0, unsigned int *seed1, t_intersection res, __global float3 *albedo_textures, __global float *perlin, __constant t_object *n_objects);
float3			get_spotlight_light(__constant t_object *objects, __constant t_scene *scene, __constant t_spotlight *spotlights, unsigned int *seed0, unsigned int *seed1, t_intersection res, __global float3 *albedo_textures, __global float *perlin, __constant t_object *n_objects);
float3			get_paralel_light(__constant t_object *objects, __constant t_scene *scene, t_intersection res, __global float3 *albedo_textures, __global float *perlin, __constant t_object *n_objects);
t_intersection	get_intersect(__constant t_object *objects, __constant t_scene *scene, t_ray ray, unsigned int *seed0, unsigned int *seed1, __constant t_spotlight *spotlights, t_negative negative);

t_negative		range_cylinder(t_object object, t_ray ray);
t_negative		range_sphere(t_object object, t_ray ray);
t_negative		get_negative_range(__constant t_object *n_objects, __constant t_scene *scene, t_ray ray);
float3			get_environment_radiance(__global float3 *environment_map, __constant t_scene *scene, t_ray ray, t_negative neg);
float3			get_environment_light(__constant t_object *objects, __global float3 *environment_map, __constant t_scene *scene, unsigned int *seed0, unsigned int *seed1, t_intersection issect, __constant t_object *n_objects, __global float3 *albedo_textures, __global float *perlin);

t_matrix		inverse_matrix(t_matrix m);
t_matrix		init_transform_matrix(float3 e1, float3 e2, float3 e3);
float3			mult_matrix_vec(t_matrix m, float3 v);
float3			mult_matrix_from_vectors_vec(float3 a, float3 b, float3 c, float3 v);
float3			back_transform_vec(t_object object, float3 v);

float3			clamp_vec(float3 v);
float			my_clamp(float x);
int				to_int(float x, float gamma);
float			to_float(float x);

float3			clamp_vec(float3 v)
{
	float m;

	if (v.x < v.y)
		m = (v.y < v.z) ? v.z : v.y;
	else
		m = (v.x < v.z) ? v.z : v.x;
	if (m < EPS)
		return ((float3)(0, 0, 0));
	else if (m < 1)
		return v;
	else
		return (v / m);
}

static int		isnan_float3(float3 v)
{
	return (isnan(v.x) || isnan(v.y) || isnan(v.z));
}

float			my_clamp(float x)
{
	if (x < 0)
		return (0);
	else
		return (x > 1 ? 1 : x);
}

int				to_int(float x, float gamma)
{
	return (int)(pow(my_clamp(x), 1.0f / gamma) * 255 + 0.5);
}

float			to_float(float x)
{
	return (pow(my_clamp(x), 1.0f / 2.2f) * 255 + 0.5f);	
}

t_matrix		inverse_matrix(t_matrix m)
{
	float d1, d2, d3;
	d1 = m.b.y * m.c.z - m.c.y * m.b.z;
	d2 = m.b.x * m.c.z - m.b.z * m.c.x;
	d3 = m.b.x * m.c.y - m.c.x * m.b.y;
	float det = m.a.x * d1 -
		m.a.y * d2 +
		m.a.z * d3;

	float invdet = 1 / det;

	t_matrix minv;
	minv.a.x = d1 * invdet;
	minv.a.y = (m.a.z * m.c.y - m.a.y * m.c.z) * invdet;
	minv.a.z = (m.a.y * m.b.z - m.a.z * m.b.y) * invdet;
	minv.b.x = -d2 * invdet;
	minv.b.y = (m.a.x * m.c.z - m.a.z * m.c.x) * invdet;
	minv.b.z = (m.b.x * m.a.z - m.a.x * m.b.z) * invdet;
	minv.c.x = d3 * invdet;
	minv.c.y = (m.c.x * m.a.y - m.a.x * m.c.y) * invdet;
	minv.c.z = (m.a.x * m.b.y - m.b.x * m.a.y) * invdet;
	return minv;
}

t_matrix		init_transform_matrix(float3 e1, float3 e2, float3 e3)
{
	t_matrix m;

	m.a.x = e1.x;
	m.b.x = e1.y;
	m.c.x = e1.z;

	m.a.y = e2.x;
	m.b.y = e2.y;
	m.c.y = e2.z;

	m.a.z = e3.x;
	m.b.z = e3.y;
	m.c.z = e3.z;
	return m;
}

float3			mult_matrix_vec(t_matrix m, float3 v)
{
	float3 res, tmp;
	
	tmp = m.a * v;
	res.x = tmp.x + tmp.y + tmp.z;
	tmp = m.b * v;
	res.y = tmp.x + tmp.y + tmp.z;
	tmp = m.c * v;
	res.z = tmp.x + tmp.y + tmp.z;
	return res;
}

float3			mult_matrix_from_vectors_vec(float3 a, float3 b, float3 c, float3 v)
{
	float3 res, tmp;
	
	tmp = a * v;
	res.x = tmp.x + tmp.y + tmp.z;
	tmp = b * v;
	res.y = tmp.x + tmp.y + tmp.z;
	tmp = c * v;
	res.z = tmp.x + tmp.y + tmp.z;
	return res;
}

float3			back_transform_vec(t_object object, float3 v)
{
	return (float3)(v.x * object.edge0.x + v.y * object.edge1.x + v.z * object.dir.x,
					v.x * object.edge0.y + v.y * object.edge1.y + v.z * object.dir.y,
					v.x * object.edge0.z + v.y * object.edge1.z + v.z * object.dir.z);
}

int				my_sgn(double x)
{
	if (x < -EPS)
		return (-1);
	return (x > EPS);
}

t_quaternion	init_quat(float3 v, float w)
{
	t_quaternion	new_quat;
	float			len;

	v = fast_normalize(v);
	new_quat.v = v * sin(w / 2);
	new_quat.w = cos((float)(w / 2.0));
	len = 1 / sqrt(1 + new_quat.w * new_quat.w);
	new_quat.w *= len;
	new_quat.v = new_quat.v * len;
	return (new_quat);
}

void			normalise_quat(t_quaternion *q)
{
	float len;

	len = 1 / sqrt(q->w * q->w + dot(q->v, q->v));
	q->w *= len;
	q->v = q->v * len;
}

t_quaternion	invert_quat(t_quaternion q)
{
	t_quaternion	res;

	res.w = q.w;
	res.v = q.v * -1;
	return (res);
}

t_quaternion	quat_mult_quat(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	res;

	res.w = q1.w * q2.w - q1.v.x * q2.v.x - q1.v.y * q2.v.y - q1.v.z * q2.v.z;
	res.v.x = q1.w * q2.v.x + q1.v.x * q2.w + q1.v.y * q2.v.z - q1.v.z * q2.v.y;
	res.v.y = q1.w * q2.v.y - q1.v.x * q2.v.z + q1.v.y * q2.w + q1.v.z * q2.v.x;
	res.v.z = q1.w * q2.v.z + q1.v.x * q2.v.y - q1.v.y * q2.v.x + q1.v.z * q2.w;
	return (res);
}

t_quaternion	quat_mult_3(t_quaternion q, float3 v)
{
	t_quaternion	res;

	res.w = -q.v.x * v.x - q.v.y * v.y - q.v.z * v.z;
	res.v.x = q.w * v.x + q.v.y * v.z - q.v.z * v.y;
	res.v.y = q.w * v.y - q.v.x * v.z + q.v.z * v.x;
	res.v.z = q.w * v.z + q.v.x * v.y - q.v.y * v.x;
	return (res);
}

float3			quat_transform_vec3(t_quaternion q, float3 v)
{
	t_quaternion	tmp;

	tmp = quat_mult_3(q, v);
	tmp = quat_mult_quat(tmp, invert_quat(q));
	return (fast_normalize(tmp.v));
}

t_complex		sqrt_complex(t_complex c)
{
	t_complex res;
	double k = sqrt(c.Re * c.Re + c.Im * c.Im);
	res.Re = sqrt((k + c.Re) * 0.5);
	res.Im = ((c.Im > 0) ? 1 : -1) * sqrt((k - c.Re) * 0.5);
	return res;
}

t_basis			get_basis_from_vec(float3 dir)
{
	t_basis basis;

	basis.w = dir;
	basis.u = fast_normalize(cross((fabs(basis.w.x) > 1e-6f) ? (float3)(0.f, 1.f, 0.f) : (float3)(1.f, 0.f, 0.f), basis.w));
	basis.v = fast_normalize(cross(basis.w, basis.u));
	return (basis);
}

void			float_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int				solve_quadratic(t_quad *q)
{
	float	d;
	float	sol;

	d = q->b * q->b - 4 * q->a * q->c;
	if (d < 0)
		return (0);
	else if (d == 0)
	{
		q->t1 = -0.5f * q->b / q->a;
		q->t2 = q->t1;
		return (1);
	}
	else
	{
		sol = (q->b > 0) ? -0.5f * (q->b + sqrt(d)) : -0.5f * (q->b - sqrt(d));
		q->t1 = sol / q->a;
		q->t2 = q->c / sol;
	}
	if (q->t1 > q->t2)
		float_swap(&q->t1, &q->t2);
	return (2);
}

static void		double_swap(double *a, double *b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		solve_quadratic_(double a, double b, double c, t_complex *roots)
{
	double d;
	double sol;

	d = b * b - 4 * a * c;
	if (d < 0)
		return 0;
	else if (d == 0)
	{
		roots[0].Re = -0.5 * b / a;
		return 1;
	}
	else
	{
		sol = (b > 0) ? -0.5 * (b + sqrt(d)) : -0.5 * (b - sqrt(d));
		roots[0].Re = sol / a;
		roots[1].Re = c / sol;
		if (roots[0].Re > roots[1].Re)
			double_swap(&roots[0].Re, &roots[1].Re);
		return 2;
	}
}

static int		solve_cubic(double b, double c, double d, t_complex *roots)
{
    if (d == 0)
    	return (solve_quadratic_(1, b, c, roots));
    double disc, q, r, dum1, s, t, term1, r13;

    q = (3.0 * c - (b * b)) / 9.0;
    r = -(27.0 * d) + b * (9.0 * c - 2.0 * (b * b));
    r /= 54.0;
    disc = q * q * q + r * r;
    roots[0].Im = 0.0;
    term1 = (b / 3.0);
    if (disc > 1e-8)
    {
        s = r + sqrt(disc);
        s = ((s < 0) ? -pow(-s, (1.0 / 3.0)) : pow(s, (1.0 / 3.0)));
        t = r - sqrt(disc);
        t = ((t < 0) ? -pow(-t, (1.0 / 3.0)) : pow(t, (1.0 / 3.0)));
        roots[0].Re = -term1 + s + t;
        term1 += (s + t)/2.0;
        roots[2].Re = roots[1].Re = -term1;
        term1 = sqrt(3.0) * (-t + s) / 2.0;
        roots[1].Im = term1;
        roots[2].Im = -term1;
        return 1;
    } 
    roots[2].Im = roots[1].Im = 0.0;
    if (fabs(disc) < 1e-8)
    {
        r13 = ((r < 0.0) ? -pow(-r, (1.0 / 3.0)) : pow(r, (1.0 / 3.0)));
        roots[0].Re = -term1 + 2.0 * r13;
        roots[2].Re = roots[1].Re = -(r13 + term1);
        return 2;
    }
    q = -q;
    dum1 = q * q * q;
    dum1 = acos(r / sqrt(dum1));
    r13 = 2.0 * sqrt(q);
    roots[0].Re = -term1 + r13 * cos(dum1 / 3.0);
    roots[1].Re = -term1 + r13 * cos((dum1 + 2.0 * MY_PI) / 3.0);
    roots[2].Re = -term1 + r13 * cos((dum1 + 4.0 * MY_PI) / 3.0);
    return 3;
}

static int		solve_quartic(double b, double c, double d, double e, double *roots)
{
	double f, g, h;
	t_complex	cubic_roots[3];

	f = c - b * b * 0.375;
	g = d + b * b * b * 0.125 - b * c * 0.5;
	h = e - 3 * b * b * b * b / 256 + b * b * c / 16 - b * d * 0.25;
	int	n_cubic_roots;

	n_cubic_roots = solve_cubic(f * 0.5, (f * f - 4 * h) / 16.0, -g * g / 64.0, cubic_roots);
	if (n_cubic_roots == 1)
	{
		t_complex p, q;
		double r, s;
		p = sqrt_complex(cubic_roots[1]);
		q = sqrt_complex(cubic_roots[2]);
		r = -g / (8.0 * (p.Re * p.Re + p.Im * p.Im));
		s = b * 0.25;
		if (isnan(p.Re) || isnan(p.Im))
			return (0);
		roots[0] = p.Re + q.Re + r - s;
		roots[1] = -p.Re - q.Re + r - s;
		roots[2] = -1.0;
		roots[3] = -1.0;
		return 2;
	}
	else if (n_cubic_roots == 2 || n_cubic_roots == 3)
	{
		double r, s, p, q;
		if (n_cubic_roots == 2)
		{
			if (cubic_roots[0].Re < EPS || cubic_roots[1].Re < EPS)
				return (0);
			p = sqrt(cubic_roots[0].Re);
			q = sqrt(cubic_roots[1].Re);
		}
		else
		{
			if (cubic_roots[0].Re < EPS)
			{
				if (cubic_roots[1].Re < EPS || cubic_roots[2].Re < EPS)
					return (0);
				else
				{
					p = sqrt(cubic_roots[1].Re);
					q = sqrt(cubic_roots[2].Re);
				}
			}
			else
			{
				if (cubic_roots[1].Re > EPS)
				{
					p = sqrt(cubic_roots[0].Re);
					q = sqrt(cubic_roots[1].Re);
				}
				else if (cubic_roots[2].Re > EPS)
				{
					p = sqrt(cubic_roots[0].Re);
					q = sqrt(cubic_roots[2].Re);
				}
				else
					return (0);
			}
		}
		if (isnan(p) || isnan(q))
			return (0);
		r = -g / (8 * p * q);
		s = b  * 0.25;
		roots[0] = p + q + r - s;
		roots[1] = p - q - r - s;
		roots[2] = -p + q - r - s;
		roots[3] = -p - q + r - s;
		return (4);
	}
	else
		return (0);
}

static int		lean_in_range(float2 negative_range, float t)
{
	return (t >= negative_range.x && t <= negative_range.y);
}

float			intersect_sphere(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n)
{
	t_quad		q;
	// float3		point1 = object.point1 + object.upsilon * ray.t;

	*n = 0;
	q.a = 1.0f;
	q.b = 2.0f * dot(ray.d, ray.o - object.point1);
	q.c = object.c2 + dot(ray.o, ray.o) - 2 * dot(ray.o, object.point1) - object.radius2;
	if (!solve_quadratic(&q))
		return (-1);
	if (q.t1 < EPS && q.t2 < EPS) // I
		return (-1);
	else if (q.t1 > EPS && q.t2 > EPS)
	{
		if (lean_in_range(negative.range, q.t1) && lean_in_range(negative.range, q.t2))
			return (-1);
		else if (lean_in_range(negative.range, q.t1) && !lean_in_range(negative.range, q.t2))
		{
			if (negative.range.y < q.t2 && negative.range.y > EPS)
			{
				*hit_point_tmp = negative.hit_point;
				*normal_tmp = negative.normal;
				*n = 1;
				return (negative.range.y + EPS);
			}
			else
			{
				*hit_point_tmp = ray.o + ray.d * q.t2;
				*normal_tmp = fast_normalize(*hit_point_tmp - object.point1);
				return (q.t2);	
			}
		}
		else if (!lean_in_range(negative.range, q.t1))
		{
			*hit_point_tmp = ray.o + ray.d * q.t1;
			*normal_tmp = fast_normalize(*hit_point_tmp - object.point1);
			return (q.t1);
		}
	}
	else if (q.t1 < EPS && q.t2 > EPS)
	{
		if (lean_in_range(negative.range, q.t2))
			return (-1);
		else
		{
			if (negative.range.y < q.t2 && negative.range.y > EPS)
			{
				*hit_point_tmp = negative.hit_point;
				*normal_tmp = negative.normal;
				*n = 1;
				return (negative.range.y + EPS);
			}
			else
			{
				*hit_point_tmp = ray.o + ray.d * q.t2;
				*normal_tmp = fast_normalize(*hit_point_tmp - object.point1);
				return (q.t2);
			}
		}
	}
	return (-1);
}

float			intersect_plane(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n)
{
	// float3		point1 = object.point1 + object.upsilon * ray.t;
	float3 point1 = object.point1;

	float denom = dot(object.n, ray.d);
	*n = 0;
	if (fabs(denom) > EPS)
	{
		float t = dot(point1 - ray.o, object.n) / denom;
		if (t < EPS)
			return (-1);
		else
		{
			if (lean_in_range(negative.range, t))
				return (-1);
			else
			{
				*normal_tmp = (dot(object.n, ray.d) < 0) ? object.n : -1 * object.n;
				*hit_point_tmp = ray.o + ray.d * t;
				return (t);
			}
		}
	}
	return (-1);
}

bool			check_for_m_cone(t_ray ray, t_object object, t_quad q, float t)
{
	float m;

	float3 v = ray.o + ray.d * t;
	v = v - object.point1;
	m = dot(v, object.dir);
	if (m <= object.top && m >= -object.bot)
		return (true);
	return (false);
}

float			intersect_cone(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	t_quad	q;

	q.x = ray.o - object.point1;
	float dv = dot(object.dir, ray.d);
	float xv = dot(q.x, object.dir);
	float kk = object.k * object.k;

	q.a = 1.0f - kk * dv * dv;
	q.b = 2.0f * (dot(ray.d, q.x) - kk * dv * xv);
	q.c = dot(q.x, q.x) - kk * xv * xv;
	if (!solve_quadratic(&q))
		return (-1);

	t_object disk;
	bool down = dot(ray.d, object.dir) > 0;
	disk.point1 = object.point1 + object.dir * (down ? -object.bot : object.top);
	disk.n = down ? -object.dir : object.dir;
	disk.radius = (down ? object.bot : object.top) * sqrt(kk - 1);
	float3 normal_disk, hit_point_disk;
	float t_disk = intersect_disk(disk, ray, &normal_disk, &hit_point_disk);

	float t;
	if (q.t1 < EPS && q.t2 < EPS)
		return (-1);
	else if (q.t1 > EPS)
	{
		if (check_for_m_cone(ray, object, q, q.t1))
		{
			if (t_disk > EPS && t_disk < q.t1)
			{
				*hit_point_tmp = ray.o + ray.d * t_disk;
				*normal_tmp = disk.n;
				return (t_disk);		
			}
			else
				t = q.t1;
		}
		else
		{
			if (check_for_m_cone(ray, object, q, q.t2))
			{
				if (t_disk > EPS && t_disk < q.t2)
				{
					*hit_point_tmp = ray.o + ray.d * t_disk;
					*normal_tmp = disk.n;
					return (t_disk);
				}
				else
					t = q.t2;
			}
			else
				return -1;
		}
	}
	else if (q.t1 < EPS)
	{
		if (t_disk > EPS && t_disk < q.t2)
		{
			*hit_point_tmp = ray.o + ray.d * t_disk;
			*normal_tmp = disk.n;
			return (t_disk);
		}
		else
		{
			if (check_for_m_cone(ray, object, q, q.t2))
				t = q.t2;
			else
				return -1;
		}
	}
	else
		return (-1);

	if (t < EPS)
		return (-1);
	*hit_point_tmp = ray.o + ray.d * t;
	*normal_tmp = *hit_point_tmp - object.point1;
	float m = dot(*normal_tmp, object.dir);
	*normal_tmp -= kk * m * object.dir;
	*normal_tmp = fast_normalize(*normal_tmp);
	return (t);
}

float			intersect_cylinder(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n)
{
	t_quad	q;
	*n = 0;


	q.x = ray.o - object.point1;
	float dd = dot(ray.d, object.dir);
	float xd = dot(q.x, object.dir);
	q.a = 1.0f - dd * dd;
	q.b = 2.0f * (dot(ray.d, q.x) - dd * xd);
	q.c = dot(q.x, q.x) - pow(xd, 2) - object.radius2;
	if (!solve_quadratic(&q))
		return (-1);

	q.t1 = (!check_for_m_cyl(ray, object, q, q.t1)) ? -1 : q.t1;
	q.t2 = (!check_for_m_cyl(ray, object, q, q.t2)) ? -1 : q.t2;
	float m = (dot(object.dir, ray.d) > 0) ? 0 : object.top;
	t_object disk;
	disk.point1 = object.point1 + object.dir * m;
	disk.n = (m > EPS) ? object.dir : -object.dir;
	disk.radius = object.radius;
	float t1 = intersect_disk(disk, ray, normal_tmp, hit_point_tmp);
	disk.point1 = object.point1 + object.dir * ((m > EPS) ? 0 : object.top);
	disk.n = (m > EPS) ? -object.dir : object.dir;
	float3 min_normal = *normal_tmp, min_hp = *hit_point_tmp;
	float t2 = intersect_disk(disk, ray, normal_tmp, hit_point_tmp);
	if (t1 < EPS && t2 < EPS && q.t1 < EPS && q.t2 < EPS)
		return (-1);
	else if (t1 < EPS && t2 < EPS && q.t1 > EPS && q.t2 > EPS)
	{
		if (lean_in_range(negative.range, q.t1) && lean_in_range(negative.range, q.t2))
			return (-1);
		else if (lean_in_range(negative.range, q.t1) && !lean_in_range(negative.range, q.t2))
		{
			*hit_point_tmp = negative.hit_point;
			*normal_tmp = negative.normal;
			*n = 1;
			return (negative.range.y + EPS);
		}
		else if (!lean_in_range(negative.range, q.t1))
		{
			*hit_point_tmp = ray.o + ray.d * q.t1;
			float tmp = dot(object.dir, object.point1 - *hit_point_tmp) / dot(object.dir, object.dir);
			float3 h_p = object.dir * tmp;
			h_p = object.point1 - h_p;
			*normal_tmp = fast_normalize(*hit_point_tmp - h_p);
			return (q.t1);
		}
	}
	else if (q.t1 < EPS && q.t2 > EPS && t1 < EPS && t2 < EPS)
	{
		if (lean_in_range(negative.range, q.t2))
			return (-1);
		else
		{
			if (q.t2 < negative.range.y)
			{
				*hit_point_tmp = ray.o + ray.d * q.t2;
				float tmp = dot(object.dir, object.point1 - *hit_point_tmp) / dot(object.dir, object.dir);
				float3 h_p = object.dir * tmp;
				h_p = object.point1 - h_p;
				*normal_tmp = fast_normalize(*hit_point_tmp - h_p);
				return (q.t2);
			}
			else
			{
				*hit_point_tmp = negative.hit_point;
				*normal_tmp = negative.normal;
				*n = 1;
				return (negative.range.y + EPS);
			}
		}
	}
	else if (q.t1 > EPS && q.t2 < EPS && t1 < EPS && t2 < EPS)
	{
		if (lean_in_range(negative.range, q.t1))
			return (-1);
		*hit_point_tmp = ray.o + ray.d * q.t1;
		float tmp = dot(object.dir, object.point1 - *hit_point_tmp) / dot(object.dir, object.dir);
		float3 h_p = object.dir * tmp;
		h_p = object.point1 - h_p;
		*normal_tmp = fast_normalize(*hit_point_tmp - h_p);
		return (q.t1);	
	}
	else if (t1 > EPS && t2 > EPS)
	{
		if (lean_in_range(negative.range, t1) && lean_in_range(negative.range, t2))
			return (-1);
		else if (lean_in_range(negative.range, t1) && !lean_in_range(negative.range, t2))
		{
			*hit_point_tmp = negative.hit_point;
			*normal_tmp = negative.normal;
			*n = 1;
			return (negative.range.y + EPS);
		}
		else if (!lean_in_range(negative.range, t1))
		{
			*hit_point_tmp = min_hp;
			*normal_tmp = min_normal;
			return (t1);
		}
	}
	else if (q.t2 > EPS && q.t1 < EPS)
	{
		if (lean_in_range(negative.range, q.t2) && lean_in_range(negative.range, t1))
			return (-1);
		else if (lean_in_range(negative.range, t1) && !lean_in_range(negative.range, q.t2))
		{
			*hit_point_tmp = negative.hit_point;
			*normal_tmp = negative.normal;
			*n = 1;
			return (negative.range.y + EPS);
		}
		else
		{
			*hit_point_tmp = min_hp;
			*normal_tmp = min_normal;
			return (t1);
		}
	}
	else if (q.t2 < EPS && q.t1 > EPS)
	{
		if (lean_in_range(negative.range, q.t1) && lean_in_range(negative.range, t2))
			return (-1);
		else if (lean_in_range(negative.range, q.t1) && !lean_in_range(negative.range, t2))
		{
			*hit_point_tmp = negative.hit_point;
			*normal_tmp = negative.normal;
			*n = 1;
			return (negative.range.y + EPS);
		}
		else
		{
			*hit_point_tmp = ray.o + ray.d * q.t1;
			float tmp = dot(object.dir, object.point1 - *hit_point_tmp) / dot(object.dir, object.dir);
			float3 h_p = object.dir * tmp;
			h_p = object.point1 - h_p;
			*normal_tmp = fast_normalize(*hit_point_tmp - h_p);
			return (q.t1);	
		}
	}
	else if (t1 < EPS && t2 > EPS && q.t1 < EPS && q.t2 < EPS)
	{
		if (lean_in_range(negative.range, t2))
			return (-1);
		else
		{
			if (t2 > negative.range.y)
			{
				*hit_point_tmp = negative.hit_point;
				*normal_tmp = negative.normal;
				*n = 1;
				return (negative.range.y + EPS);
			}
			else
				return (t2);
		}
	}
	else if (q.t1 > EPS && q.t2 > EPS)
	{
		if (lean_in_range(negative.range, q.t1) && lean_in_range(negative.range, q.t2))
			return (-1);
		else if (lean_in_range(negative.range, q.t1) && !lean_in_range(negative.range, q.t2))
		{
			*hit_point_tmp = negative.hit_point;
			*normal_tmp = negative.normal;
			*n = 1;
			return (negative.range.y + EPS);
		}
		else
		{
			*hit_point_tmp = ray.o + ray.d * q.t1;
			float tmp = dot(object.dir, object.point1 - *hit_point_tmp) / dot(object.dir, object.dir);
			float3 h_p = object.dir * tmp;
			h_p = object.point1 - h_p;
			*normal_tmp = fast_normalize(*hit_point_tmp - h_p);
			return (q.t1);
		}
	}
	return (-1);
}

static float	simplified_cylinder_intersect(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	t_quad	q;

	*normal_tmp = 0;
	*hit_point_tmp = 0;
	q.x = ray.o - object.point1;
	float dd = dot(ray.d, object.dir);
	float xd = dot(q.x, object.dir);
	q.a = 1.0f - dd * dd;
	q.b = 2.0f * (dot(ray.d, q.x) - dd * xd);
	q.c = dot(q.x, q.x) - xd * xd - object.radius2;
	if (!solve_quadratic(&q))
		return (-1);
	if (q.t1 < EPS && q.t2 < EPS)
		return -1;
	else if (q.t1 > EPS && q.t2 > EPS)
	{
		float m1 = dd * q.t1 + xd;
		if (!(m1 >= 0 && m1 <= object.top))
			return -1;

		*hit_point_tmp = ray.d * q.t1 + ray.o;
		float tmp = dot(object.dir, object.point1 - *hit_point_tmp) / dot(object.dir, object.dir);
		float3 h_p = object.dir * tmp;
		h_p = object.point1 - h_p;
		*normal_tmp = fast_normalize(*hit_point_tmp - h_p);
		return q.t1;
	}
	else
		return -1;
}

static float	simplified_sphere_intersect(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	t_quad		q;

	*normal_tmp = 0;
	*hit_point_tmp = 0;
	q.a = 1.0f;
	q.b = 2.0f * dot(ray.d, ray.o - object.point1);
	q.c = object.c2 + dot(ray.o, ray.o) - 2 * dot(ray.o, object.point1) - object.radius2;
	if (!solve_quadratic(&q))
		return -1;
	if (q.t1 < EPS)
		return -1;
	else if (q.t1 > EPS)
	{
		*hit_point_tmp = ray.o + ray.d * q.t1;
		*normal_tmp = fast_normalize(*hit_point_tmp - object.point1);
		return (q.t1);
	}
	else
		return -1;
}

bool			check_for_m_cyl(t_ray ray, t_object object, t_quad q, float t)
{
	float m;

	m = dot(ray.d, object.dir) * t + dot(q.x, object.dir);
	if ((m >= 0 && m <= object.top))
		return (true);
	return (false);
}

float			intersect_dna(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	ray.o -= object.point1;
	ray.o = mult_matrix_from_vectors_vec(object.a, object.b, object.c, ray.o);
	ray.d = fast_normalize(mult_matrix_from_vectors_vec(object.a, object.b, object.c, ray.d));

	t_quad		q;
	q.x = ray.o - (float3)(0, 0, -object.k);
	q.a = 1.0f - ray.d.z * ray.d.z;
	q.b = 2.0f * (dot(ray.d, q.x) - ray.d.z * q.x.z);
	// q.c = dot(q.x, q.x) - q.x.z * q.x.z - object.edge2.z;
	q.c = dot(q.x, q.x) - q.x.z * q.x.z - (object.radius + 0.01f) * (object.radius + 0.01f);
	if (!solve_quadratic(&q))
		return -1;


	if (q.t1 < EPS && q.t2 < EPS)
		return -1;

	else if (q.t1 > EPS)
	{
		float3 point1 = ray.d * q.t1 + ray.o;
		float3 point2 = ray.d * q.t2 + ray.o;
		float dist1 = point1.z;
		float dist2 = point2.z;

		if ((dist1 < object.bot && dist1 > object.top) &&
		    (dist2 < object.bot && dist2 > object.top))
			return -1;
	}
	else if (q.t2 > EPS)
	{
		float3 point2 = ray.d * q.t2 + ray.o;
		float dist2 = point2.z;

		if (dist2 < -object.k && dist2 > object.top)
			return -1;
	}
	else
		return -1;

	t_object sphere1, sphere2, cylinder;

	sphere1.radius2 = object.radius2;
	sphere2.radius2 = sphere1.radius2;
	cylinder.top = object.radius - 2.0f * sqrt(sphere1.radius2);
	cylinder.radius2 = 0.09f * sphere1.radius2;

	float alpha = 2.0f * MY_PI / object.frequency;
	float ground_point = (object.radius - sqrt(sphere1.radius2)) * 0.5f;

	float	roots[3];
	float3	hit_point[3], normal[3], h, n;

	float tmin = INFIN + 1.0f;
	int start_floor = 0;
	while (start_floor < object.period)
	{
		cylinder.point1 = (float3)(cos(alpha * start_floor) * ground_point,
									-sin(alpha * start_floor) * ground_point, 0);
		// cylinder.point1 = (float3)(cos(object.edge2.x * start_floor) * object.edge2.y,
		// 						  -sin(object.edge2.x * start_floor) * object.edge2.y, 0);
		cylinder.dir = -1 * fast_normalize(cylinder.point1);
		cylinder.point1 += (float3)(0, 0, start_floor * object.k);

		sphere1.point1 = cylinder.point1;
		sphere1.c2 = dot(sphere1.point1, sphere1.point1);

		sphere2.point1 = sphere1.point1 + cylinder.top * cylinder.dir;
		sphere2.c2 = dot(sphere2.point1, sphere2.point1);

		roots[0] = simplified_sphere_intersect(sphere1, ray, &normal[0], &hit_point[0]);
		roots[1] = simplified_sphere_intersect(sphere2, ray, &normal[1], &hit_point[1]);
		roots[2] = simplified_cylinder_intersect(cylinder, ray, &normal[2], &hit_point[2]);

		int i = -1;
		while (++i < 3)
		{
			if (roots[i] > EPS && roots[i] < tmin)
			{
				tmin = roots[i];
				h = hit_point[i];
				n = normal[i];
			}
		}
		start_floor++;
	}

	*hit_point_tmp = back_transform_vec(object, h) + object.point1;
	*normal_tmp = fast_normalize(back_transform_vec(object, n));
	return tmin;
}

float			intersect_elipsoid(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	t_quad	q;
	// float3	point1 = object.point1 + object.upsilon * ray.t;

	q.x = ray.o - object.point1;
	float	A1 = 2.0f * object.k * dot(ray.d, object.dir),
			A2 = object.radius2 + 2.0f * object.k * dot(q.x, object.dir) - object.k;
	q.a = 4.0f * object.radius2;
	q.c = q.a * dot(q.x, q.x) - A2 * A2;
	q.b = 2.0f * (q.a * dot(ray.d, q.x) - A1 * A2);
	q.a -= A1 * A1;
	if (!solve_quadratic(&q))
		return -1;

	float t;
	if (q.t1 < EPS && q.t2 < EPS)
		return (-1);
	else if (q.t1 > EPS)
		t = q.t1;
	else if (q.t1 < EPS)
		t = q.t2;
	else
		return (-1);

	*hit_point_tmp = ray.o + ray.d * t;
	float3 Cmid = object.point1 + object.dir * object.k * 0.5f;
	float3 R = *hit_point_tmp - Cmid;
	*normal_tmp = fast_normalize(R - object.dir * pow(object.k / object.radius, 2) * dot(R, object.dir));
	return t;
}

float			intersect_paraboloid(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n)
{
	t_quad	q;
	// float3	point1 = object.point1 + object.upsilon * ray.t;
	float3	point1 = object.point1;

	q.x = ray.o - point1;
	float xd = dot(q.x, object.dir);
	float dd = dot(ray.d, object.dir);
	q.a = 1.0f - dd * dd;
	q.b = 2.0f * (dot(ray.d, q.x) - dd * (xd + 2.0f * object.k));
	q.c = dot(q.x, q.x) - xd * (xd + 4.0f * object.k);
	if (!solve_quadratic(&q))
		return (-1);

	float3 hp1 = ray.o + ray.d * q.t1;
	float3 hp2 = ray.o + ray.d * q.t2;
	float3 vec_hp1 = hp1 - point1;
	float3 vec_hp2 = hp2 - point1;

	if (dot(vec_hp1, object.dir) > object.top)
		q.t1 = -1;
	if (dot(vec_hp2, object.dir) > object.top)
		q.t2 = -1;

	if (q.t1 < EPS && q.t2 < EPS) // I
		return (-1);
	else if (q.t1 > EPS && q.t2 > EPS)
	{
		if (lean_in_range(negative.range, q.t1) && lean_in_range(negative.range, q.t2))
			return (-1);
		else if (lean_in_range(negative.range, q.t1) && !lean_in_range(negative.range, q.t2))
		{
			if (negative.range.y < q.t2 && negative.range.y > EPS)
			{
				*hit_point_tmp = negative.hit_point;
				*normal_tmp = negative.normal;
				*n = 1;
				return (negative.range.y + EPS);
			}
			else
			{
				*hit_point_tmp = hp2;
				*normal_tmp = hp2 - point1;
				float m = dot(*normal_tmp, object.dir);
				*normal_tmp = fast_normalize(*normal_tmp - object.dir * (m + object.k));
				return (q.t2);
			}
		}
		else if (!lean_in_range(negative.range, q.t1))
		{
			*hit_point_tmp = hp1;
			*normal_tmp = hp1 - point1;
			float m = dot(*normal_tmp, object.dir);
			*normal_tmp = fast_normalize(*normal_tmp - object.dir * (m + object.k));
			return (q.t1);
		}
	}
	else if (q.t1 < EPS && q.t2 > EPS)
	{
		if (lean_in_range(negative.range, q.t2))
			return (-1);
		else
		{
			if (negative.range.y < q.t2 && negative.range.y > EPS)
			{
				*hit_point_tmp = negative.hit_point;
				*normal_tmp = negative.normal;
				*n = 1;
				return (negative.range.y + EPS);
			}
			else
			{
				*hit_point_tmp = hp2;
				*normal_tmp = hp2 - point1;
				float m = dot(*normal_tmp, object.dir);
				*normal_tmp = fast_normalize(*normal_tmp - object.dir * (m + object.k));
				return (q.t2);
			}
		}
	}
	return (-1);
}

float			intersect_ring(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	int dummy;

	t_object cylinder;
	cylinder.dir = object.dir;
	cylinder.point1 = object.point1;
	cylinder.radius = object.k;
	cylinder.top = object.top;
	t_negative negative = range_cylinder(cylinder, ray);
	return (intersect_cylinder(object, ray, normal_tmp, hit_point_tmp, negative, &dummy));
}

float			intersect_triangle(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float	denom, t;
	float3	tmp;

	denom = dot(object.n, ray.d);
	if (fabs(denom) < EPS)
		return (-1);
	float3 point1 = object.point1;
	t = dot(point1 - ray.o, object.n) / denom;
	if (t < EPS)
		return (-1);
	*hit_point_tmp = ray.o + ray.d * t;
	tmp = cross(object.edge0, *hit_point_tmp - point1); 
	if (dot(object.n, tmp) < 0)
		return (-1);
	tmp = cross(object.edge1, *hit_point_tmp - object.point2);
	if (dot(object.n, tmp) < 0)
		return (-1);
	tmp = cross(object.edge2, *hit_point_tmp - object.point3);
	if (dot(object.n, tmp) < 0)
		return (-1);
	*normal_tmp = (dot(object.n, ray.d) < 0) ? object.n : -1 * object.n;
	return (t);
}

static float	intersect_triangle_(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
    float3 h, s, q, edge1, edge2, n;
    edge1 = object.point2 - object.point1;
    edge2 = object.point3 - object.point1;
    n = fast_normalize(cross(edge1, edge2));
    float a, f, u, v;
    h = cross(ray.d, edge2);
    a = dot(edge1, h);
    if (a > -EPS && a < EPS)
        return -1;
    f = 1.0f / a;
    s = ray.o - object.point1; 
    u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return -1;
    q = cross(s, edge1);
    v = f * dot(ray.d, q);
    if (v < 0.0 || u + v > 1.0)
        return -1;
    float t = f * dot(edge2, q);
    if (t > EPS)
    {
        *hit_point_tmp = ray.o + ray.d * t;
        *normal_tmp = (dot(n, ray.d) < 0) ? n : -1 * n;
        return t;
    }
    else
        return -1;
}

float			intersect_cubohedron(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float		root[2];
	float3		normal[2];
	float3		hit_point[2];

	t_negative neg;
	int dummy;
	neg.range.x = -INFIN;
	neg.range.y = 0.0f;

	root[0] = intersect_cube(object, ray, &normal[0], &hit_point[0], neg, &dummy);

 
	object.point1 = object.point2;
	object.point2 = object.point3;
	object.edge0 = object.upsilon;
	object.edge1 = object.b;
	object.edge2 = object.c;
	object.point3 = object.n;
	root[1] = intersect_octahedron(object, ray, &normal[1], &hit_point[1]);

	float tmin = INFIN + 1.0f;
	int i = -1;
	while (++i < 2)
	{
		if (root[i] > EPS && root[i] < tmin)
		{
			tmin = root[i];
			*normal_tmp = normal[i];
			*hit_point_tmp = hit_point[i];
		}
	}

	if (tmin > INFIN)
		return -1;
	return tmin;
}

float			intersect_octahedron(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	t_quad		q;
	q.a = 1.0f;
	q.b = 2.0f * dot(ray.d, ray.o - object.point3);
	q.c = object.c2 + dot(ray.o, ray.o) - 2 * dot(ray.o, object.point3) - object.radius2;
	if (!solve_quadratic(&q))
		return -1;
	if (q.t1 < EPS && q.t2 < EPS)
		return -1;

	float roots[8];
	float3 normal[8], hit_point[8];
	t_object triangle;

	triangle.point1 = object.point1;
	triangle.point2 = object.point1 + object.edge0;
	triangle.point3 = object.point1 + object.edge2;
	roots[0] = intersect_triangle_(triangle, ray, &normal[0], &hit_point[0]);

	triangle.point2 = object.point1 + object.edge1;
	roots[1] = intersect_triangle_(triangle, ray, &normal[1], &hit_point[1]);

	triangle.point1 = object.point2;
	roots[2] = intersect_triangle_(triangle, ray, &normal[2], &hit_point[2]);

	triangle.point2 = object.point1 + object.edge0;
	roots[3] = intersect_triangle_(triangle, ray, &normal[3], &hit_point[3]);


	triangle.point1 = object.point1;
	triangle.point3 = object.point1 + object.a;
	roots[4] = intersect_triangle_(triangle, ray, &normal[4], &hit_point[4]);

	triangle.point2 = object.point1 + object.edge1;
	roots[5] = intersect_triangle_(triangle, ray, &normal[5], &hit_point[5]);

	triangle.point1 = object.point2;
	roots[6] = intersect_triangle_(triangle, ray, &normal[6], &hit_point[6]);

	triangle.point2 = object.point1 + object.edge0;
	roots[7] = intersect_triangle_(triangle, ray, &normal[7], &hit_point[7]);

	float tmin = INFIN + 1.0f, tmax = -INFIN;
	int i = -1, max_i;
	while (++i < 8)
	{
		if (roots[i] > EPS && roots[i] < tmin)
		{
			tmin = roots[i];
			*normal_tmp = normal[i];
			*hit_point_tmp = hit_point[i];
		}
		if (roots[i] > EPS && roots[i] > tmax)
		{
			max_i = i;
			tmax = roots[i];
		}
	}

	if (tmin > INFIN)
		return -1;
	return tmin;
}

float			intersect_tetrahedron(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	t_quad		q;
	q.a = 1.0f;
	q.b = 2.0f * dot(ray.d, ray.o - object.upsilon);
	q.c = object.c2 + dot(ray.o, ray.o) - 2 * dot(ray.o, object.upsilon) - object.radius2;
	if (!solve_quadratic(&q))
		return -1;
	if (q.t1 < EPS && q.t2 < EPS)
		return -1;

	float roots[4];
	float3 normal[4], hit_point[4];
	t_object triangle;

	triangle.point1 = object.point1;
	triangle.point2 = object.point1 + object.edge1;
	triangle.point3 = object.point1 + object.edge0;
	roots[0] = intersect_triangle_(triangle, ray, &normal[0], &hit_point[0]);

	triangle.point3 = object.point1 + object.edge2;
	roots[1] = intersect_triangle_(triangle, ray, &normal[1], &hit_point[1]);

	triangle.point2 = object.point1 + object.edge0;
	roots[2] = intersect_triangle_(triangle, ray, &normal[2], &hit_point[2]);

	triangle.point1 = object.point1 + object.edge1;
	roots[3] = intersect_triangle_(triangle, ray, &normal[3], &hit_point[3]);


	float tmin = INFIN + 1.0f;
	int i = -1;
	while (++i < 4)
	{
		if (roots[i] > EPS && roots[i] < tmin)
		{
			tmin = roots[i];
			*normal_tmp = normal[i];
			*hit_point_tmp = hit_point[i];
		}
	}

	if (tmin > INFIN)
		return -1;
	return tmin;
}

float			intersect_star(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float root[2];
	float3 normal[2], hit_point[2];

	root[0] = intersect_tetrahedron(object, ray, &normal[0], &hit_point[0]);

	object.point1 = object.b;
	object.edge1 = object.n;
	object.edge2 = object.a;
	object.upsilon = object.c;
	object.c2 = dot(object.c, object.c);
	root[1] = intersect_tetrahedron(object, ray, &normal[1], &hit_point[1]);

	float tmin = INFIN + 1.0f;
	int i = -1;
	while (++i < 2)
	{
		if (root[i] > EPS && root[i] < tmin)
		{
			tmin = root[i];
			*normal_tmp = normal[i];
			*hit_point_tmp = hit_point[i];
		}
	}

	if (tmin > INFIN)
		return -1;
	return tmin;
}

float			intersect_disk(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float	denom, distance, t;

	denom = dot(object.n, ray.d);
	if (fabs(denom) < EPS)
		return (-1);
	t = dot(object.point1 - ray.o, object.n) / denom;
	*hit_point_tmp = ray.o + ray.d * t;
	*normal_tmp = object.n;
	distance = fast_distance(object.point1, *hit_point_tmp);
	if (distance < object.radius)
		return (t);
	else
		return (-1);
}

float			intersect_box(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float	denom, t;
	float3	tmp;

	denom = dot(object.n, ray.d);
	if (fabs(denom) < EPS)
		return (-1);
	t = dot(object.point1 - ray.o, object.n) / denom;
	if (t < EPS)
		return (-1);

	*hit_point_tmp = ray.o + ray.d * t;

	float3	point2 = object.point1 + object.edge0,
			point3 = point2 + object.edge1,
			point4 = object.point1 + object.edge1;

	tmp = cross(object.edge0, *hit_point_tmp - object.point1);
	if (dot(object.n, tmp) < 0)
		return (-1);

	tmp = cross(object.edge1, *hit_point_tmp - point2);
	if (dot(object.n, tmp) < 0)
		return (-1);

	tmp = cross(*hit_point_tmp - point4, object.edge1);
	if (dot(object.n, tmp) < 0)
		return (-1);

	tmp = cross(*hit_point_tmp - point3, object.edge0);
	if (dot(object.n, tmp) < 0)
		return (-1);

	*normal_tmp = (dot(object.n, ray.d) < 0) ? object.n : -1 * object.n;;
	return (t);
}

float			intersect_cubehole(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	int dummy;

	t_object cylinder;
	cylinder.dir = object.dir;
	cylinder.point1 = object.point2;
	cylinder.radius = object.radius2;
	cylinder.top = object.top;
	t_negative negative = range_cylinder(cylinder, ray);
	return (intersect_cube(object, ray, normal_tmp, hit_point_tmp, negative, &dummy));
}

float			intersect_cube(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n)
{
	int			n_roots = 0;
	float		root[6];
	float3		normal[6];
	float3		hit_point[6];
	float3		edge0 = object.edge0 * object.radius,
				edge1 = object.edge1 * object.radius,
				edge2 = object.edge2 * object.radius;
	t_object	box;

	box.point1 = object.point1;
	box.edge0 = edge2;
	box.edge1 = edge1;
	box.n = object.edge0;
	if ((root[0] = intersect_box(box, ray, &normal[0], &hit_point[0])) > EPS)
		n_roots++;

	box.point1 = object.point1 + edge0;
	if ((root[1] = intersect_box(box, ray, &normal[1], &hit_point[1])) > EPS)
		n_roots++;

	box.point1 = object.point1;
	box.edge0 = edge0;
	box.edge1 = edge2;
	box.n = object.edge1;
	if ((root[2] = intersect_box(box, ray, &normal[2], &hit_point[2])) > EPS)
		n_roots++;

	box.point1 += edge1;
	if ((root[3] = intersect_box(box, ray, &normal[3], &hit_point[3])) > EPS)
		n_roots++;

	box.point1 = object.point1;
	box.edge0 = edge1;
	box.edge1 = edge0;
	box.n = object.edge2;
	if ((root[4] = intersect_box(box, ray, &normal[4], &hit_point[4])) > EPS)
		n_roots++;

	box.point1 += edge2;
	if ((root[5] = intersect_box(box, ray, &normal[5], &hit_point[5])) > EPS)
		n_roots++;

	float tmin = INFIN + 1.0f, tmax = -INFIN;
	int i = -1, max_i = 0, min_i = 0;
	while (++i < 6)
	{
		if (root[i] > EPS && root[i] < tmin)
		{
			tmin = root[i];
			min_i = i;
		}
		if (root[i] > EPS && root[i] > tmax)
		{
			max_i = i;
			tmax = root[i];
		}
	}

	if (tmin > INFIN)
		return -1;

	if (lean_in_range(negative.range, tmin) && lean_in_range(negative.range, tmax))
		return (-1);
	else if (lean_in_range(negative.range, tmin) && !lean_in_range(negative.range, tmax))
	{
		if (negative.range.y < tmax && negative.range.y > EPS)
		{
			*hit_point_tmp = negative.hit_point;
			*normal_tmp = negative.normal;
			*n = 1;
			return (negative.range.y + EPS);
		}
		else
		{
			*hit_point_tmp = hit_point[max_i];
			*normal_tmp = normal[max_i];
			return (tmax);	
		}
	}
	else if (!lean_in_range(negative.range, tmin))
	{
		if (n_roots == 1)
			*normal_tmp = -1 * normal[min_i];
		else
			*normal_tmp = normal[min_i];
		*hit_point_tmp = hit_point[min_i];
		return (tmin);
	}
	else
		return -1;
}

float			intersect_bocal(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float t_cyl, t_cone, t_sphere;
	float3 normal_cyl, normal_cone, normal_sphere;
	float3 hit_point_cyl, hit_point_cone, hit_point_sphere;
	t_object sphere, cyl, cone;

	sphere.radius = 0.45f * object.top;
	sphere.radius2 = sphere.radius * sphere.radius;
	sphere.point1 = object.point1 + object.dir * object.top;
	sphere.c2 = dot(sphere.point1, sphere.point1);
	sphere.dir = object.dir;

	cyl.dir = object.dir;
	cyl.point1 = object.point1 + object.dir * 0.01f * object.top;
	cyl.radius = 0.13f * object.top;
	cyl.radius2 = cyl.radius * cyl.radius;
	cyl.top = 0.56f * object.top;

	cone.dir = object.dir;
	cone.point1 = object.point1 + cone.dir * 0.15f * object.top;
	cone.k = 3.0f;
	cone.bot = 0.15f * object.top;
	cone.top = 0.0f;

	int i;
	t_negative n1 = range_sphere(sphere, ray);
	t_cyl = intersect_cylinder(cyl, ray, &normal_cyl, &hit_point_cyl, n1, &i);
	t_cone = intersect_cone(cone, ray, &normal_cone, &hit_point_cone);
	t_object sphere_negative = sphere;
	sphere_negative.radius *= 0.98f;
	sphere_negative.radius2 = sphere_negative.radius * sphere_negative.radius;
	sphere_negative.point1 = sphere.point1 + sphere.dir * sphere.radius * 0.07f;
	sphere_negative.c2 = dot(sphere_negative.point1, sphere_negative.point1);
	t_negative n = range_sphere(sphere_negative, ray);
	t_sphere = intersect_sphere(sphere, ray, &normal_sphere, &hit_point_sphere, n, &i);

	if (t_cyl < EPS && t_cone < EPS && t_sphere < EPS)
		return (-1);

	float min_ = min((t_cyl < EPS) ? INFIN : t_cyl, min((t_cone < EPS) ? INFIN : t_cone, (t_sphere < EPS) ? INFIN : t_sphere));
	if (fabs(min_ - t_cone) < EPS)
	{
		*normal_tmp = normal_cone;
		*hit_point_tmp = hit_point_cone;
		return (t_cone);
	}
	else if (fabs(min_ - t_cyl) < EPS)
	{
		*normal_tmp = normal_cyl;
		*hit_point_tmp = hit_point_cyl;
		return (t_cyl);
	}
	else if (fabs(min_ - t_sphere) < EPS)
	{
		*normal_tmp = normal_sphere;
		*hit_point_tmp = hit_point_sphere;
		return (t_sphere);
	}
	else
		return (-1);
}

static int		inside(t_object m, double3 h)
{
	double t;
	double s;

	t = atan2(h.y, h.x);
	if (my_sgn(sin(t * 0.5)))
		s = h.z / sin(t * 0.5);
	else
		s = my_sgn(cos(t)) ? (h.x / cos(t) - m.radius) / cos(t * 0.5) :
			(h.y / sin(t) - m.radius) / cos(t * 0.5);
	h.x -= (m.radius + s * cos(t * 0.5)) * cos(t);
	h.y -= (m.radius + s * cos(t * 0.5)) * sin(t);
	h.z -= s * sin(t * 0.5);
	if (h.x * h.x + h.y * h.y + h.z * h.z > 5e-2)
		return (0);
	return (s >= -m.radius2 && s <= m.radius2);
}

static float	right_moebius_root(int n_roots, t_complex *roots, t_ray ray, t_object mob)
{
	float	min_res = INFIN, res = -1;

	int		i = -1;
	while (++i < n_roots)
	{
		if (roots[i].Re > EPS)
		{
			double3 o = (double3)((double)ray.o.x, (double)ray.o.y, (double)ray.o.z), d = (double3)((double)ray.d.x, (double)ray.d.y, (double)ray.d.z);
			double3 hit_point = o + d * roots[i].Re;
			if (inside(mob, hit_point) && roots[i].Re < min_res)
			{
				res = roots[i].Re;
				min_res = res;
			}
		}
	}
	return res;
}

float			intersect_moebius(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	double		a, b, c, d, t;
	t_complex	cubic_roots[3];
	t_moebius	m;

	ray.o -= object.point1;
	ray.o = mult_matrix_from_vectors_vec(object.a, object.b, object.c, ray.o);
	ray.d = fast_normalize(mult_matrix_from_vectors_vec(object.a, object.b, object.c, ray.d));

	m.a = object.radius;
	m.b = ray.o.x;
	m.c = ray.d.x;
	m.d = ray.o.y;
	m.e = ray.d.y;
	m.f = ray.o.z;
	m.g = ray.d.z;
	a = m.c * m.c * m.e + m.e * m.e * m.e - 2 * m.c * m.c * m.g - 2 * m.e * m.e * m.g + m.e * m.g * m.g;
	b = (2 * m.c * m.e * m.b - 4 * m.c * m.g * m.b + m.c * m.c * m.d + 3 * m.e * m.e
		* m.d - 4 * m.e * m.g * m.d + m.g * m.g * m.d - 2 * m.c * m.c * m.f -
		2 * m.e * m.e * m.f + 2 * m.e * m.g * m.f - 2 * m.c * m.g * m.a) / a;
	c = (m.e * m.b * m.b - 2 * m.g * m.b * m.b + 2 * m.c * m.b * m.d + 3 * m.e * m.d
		* m.d - 2 * m.g * m.d * m.d - 4 * m.c * m.b * m.f - 4 * m.e * m.d * m.f + 2 * m.g * m.d
		* m.f + m.e * m.f * m.f - 2 * m.g * m.b * m.a - 2 * m.c * m.f * m.a - m.e * m.a * m.a) / a;
	d = (m.b * m.b * m.d + m.d * m.d * m.d - 2 * m.b * m.b * m.f - 2 * m.d * m.d * m.f
		+ m.d * m.f * m.f - 2 * m.b * m.f * m.a - m.d * m.a * m.a) / a;
	int	n_cubic_roots = solve_cubic(b, c, d, cubic_roots);
	if (n_cubic_roots == 0)
		return (-1);
	if ((t = right_moebius_root(n_cubic_roots, cubic_roots, ray, object)) < EPS)
		return (-1);
	
	float3	h = ray.d * (float)t + ray.o,
			n;
	n.x = 2 * h.x * h.y - 2 * object.radius * h.z - 4 * h.x * h.z;
	n.y = -object.radius * object.radius + h.x * h.x - 3 * h.y * h.y - 4 * h.y * h.z + h.z * h.z;
	n.z = -2 * object.radius * h.x - 2 * h.x * h.x - 2 * h.y * h.y + 2 * h.z * h.y;

	*hit_point_tmp = back_transform_vec(object, h) + object.point1;
	*normal_tmp = fast_normalize(back_transform_vec(object, fast_normalize(n)));
	return t;
}

float			intersect_torus(t_object obj, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	double 	roots[4];
	int		n_roots;
	double n, o, p, q;
	float3 x = ray.o - obj.point1;
	n = dot(ray.d, x);
	o = dot(x, x);
	p = dot(ray.d, obj.dir);
	q = dot(x, obj.dir);
	double b, c, d, e;
	double d_ = dot(x, x) + obj.radius * obj.radius - obj.radius2 * obj.radius2;
	b = 4.0 * n;
	c = 2.0 * d_ + 0.25 * b * b - 4.0 * obj.radius * obj.radius * (1.0 - p * p);
	d = b * d_ - 4.0 * obj.radius * obj.radius * 2.0 * (n - q * p);
	e = d_ * d_ - 4.0 * obj.radius * obj.radius * (o - q * q);
	n_roots = solve_quartic(b, c, d, e, roots);
	if (n_roots == 0)
		return -1;
	int i = -1;
	float t = -1, min_t = INFIN;
	while (++i < n_roots)
	{
		if (!isnan(roots[i]) && roots[i] > 1e-8  && roots[i] < min_t)
		{
			t = roots[i];
			min_t = t;
		}
	}
	if (t < EPS)
		return -1;
	*hit_point_tmp = ray.o + ray.d * t;
	float k = dot(*hit_point_tmp - obj.point1, obj.dir);
	if (fabs(k) - obj.radius2 > 0.1f)
		return -1;

	float3 A = *hit_point_tmp - k * obj.dir;
	float m = sqrt(obj.radius2 * obj.radius2 - k * k);
	float3 vec = obj.point1 - A;
	float len = fast_length(vec);
	vec *= ((len < obj.radius) ? -1 : 1) * m / len;
	*normal_tmp = fast_normalize(*hit_point_tmp - (A + vec));
	if (isnan_float3(*normal_tmp))
		*normal_tmp = obj.dir;
	return t;
}

float			intersect_heart(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp)
{
	float denom = dot(object.n, ray.d);
	if (fabs(denom) > EPS)
	{
		float t = dot(object.point1 - ray.o, object.n) / denom;
		if (t < EPS)
			return (-1);
		else
		{
			*hit_point_tmp = ray.o + ray.d * t;
			float3 v = *hit_point_tmp - object.point1;
			v /= object.radius;
			float	x = dot(v, object.edge0),
					y = dot(v, object.edge1);
			float f = x * x + pow((y - sqrt(fabs(x))), 2);
			if (f > 6.0f)
				return (-1);
			else
			{
				*normal_tmp = (dot(object.n, ray.d) < 0) ? object.n : -1 * object.n;
				return (t);
			}
		}
	}
	return (-1);
}

float			intersect(t_object object, t_ray ray, float3 *normal_tmp, float3 *hit_point_tmp, t_negative negative, int *n)
{
	switch (object.type) {
		case PLANE:
			return (intersect_plane(object, ray, normal_tmp, hit_point_tmp, negative, n));
		case SPHERE:
			return (intersect_sphere(object, ray, normal_tmp, hit_point_tmp, negative, n));
		case CYLINDER:
			return (intersect_cylinder(object, ray, normal_tmp, hit_point_tmp, negative, n));
		case CONE:
			return (intersect_cone(object, ray, normal_tmp, hit_point_tmp));
		case PARABOLOID:
			return (intersect_paraboloid(object, ray, normal_tmp, hit_point_tmp, negative, n));
		case DISK:
			return (intersect_disk(object, ray, normal_tmp, hit_point_tmp));
		case CUBE:
			return (intersect_cube(object, ray, normal_tmp, hit_point_tmp, negative, n));
		case CUBEHOLE:
			return (intersect_cubehole(object, ray, normal_tmp, hit_point_tmp));
		case TETRAHEDRON:
			return (intersect_tetrahedron(object, ray, normal_tmp, hit_point_tmp));
		case OCTAHEDRON:
			return (intersect_octahedron(object, ray, normal_tmp, hit_point_tmp));
		case CUBOHEDRON:
			return (intersect_cubohedron(object, ray, normal_tmp, hit_point_tmp));
		case STAR:
			return (intersect_star(object, ray, normal_tmp, hit_point_tmp));
		case ELIPSOID:
			return (intersect_elipsoid(object, ray, normal_tmp, hit_point_tmp));
		case DNA:
			return (intersect_dna(object, ray, normal_tmp, hit_point_tmp));
		case HEART:
			return (intersect_heart(object, ray, normal_tmp, hit_point_tmp));
		case BOCAL:
			return (intersect_bocal(object, ray, normal_tmp, hit_point_tmp));
		case TRIANGLE:
			return (intersect_triangle(object, ray, normal_tmp, hit_point_tmp));
		case BOX:
			return (intersect_box(object, ray, normal_tmp, hit_point_tmp));
		case MOEBIUS:
			return (intersect_moebius(object, ray, normal_tmp, hit_point_tmp));
		case TORUS:
			return (intersect_torus(object, ray, normal_tmp, hit_point_tmp));
		case RING:
			return (intersect_ring(object, ray, normal_tmp, hit_point_tmp));
		default:
			return (-1);
	}
}

float			get_random(unsigned int *seed0, unsigned int *seed1)
{
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);
	union
	{
		float f;
		unsigned int ui;
	}	res;
	res.ui = (ires & 0x007fffff) | 0x40000000;

	return (res.f - 2.f) / 2.f;
}

float3			get_direct_light(__constant t_object *objects, __constant t_scene *scene, unsigned int *seed0, unsigned int *seed1, t_intersection res, __global float3 *albedo_textures, __global float *perlin, __constant t_object *n_objects)
{
	float3 result = 0;
	int i = -1;
	while (++i < scene->amount_of_objects)
	{
		t_object	light = (t_object)objects[i];
		if (!(light.emission.x == 0.f && light.emission.y == 0.f && light.emission.z == 0.f) && res.took_place != i)
		{
			t_ray shadow_ray;

			float3 tmp = light.point1 - res.hit_point;
			float distance_to_center = fast_length(tmp);
			if (objects[res.took_place].type != MOEBIUS && dot(tmp, res.normal) < 0.0f)
				continue ;
			float cos_a_max = sqrt(1 - light.radius2 * pow((float)(distance_to_center), -2));
			t_basis basis = get_basis_from_vec(tmp / distance_to_center);
			float phi = get_random(seed0, seed1) * TWO_PI;
			float z = get_random(seed0, seed1) * (1 - cos_a_max) + cos_a_max;
			float zs = sqrt(1 - z * z);
			shadow_ray.d = fast_normalize(basis.u * zs * cos(phi) + basis.v * zs * sin(phi) + basis.w * z);
			shadow_ray.o = res.hit_point + shadow_ray.d * 0.015f;
			shadow_ray.t = 0.0f;
			float3 path_capacity;
			t_negative negative = get_negative_range(n_objects, scene, shadow_ray);
			int k = intersect_in_range(objects, scene, shadow_ray, distance_to_center - 1.0f, res, &path_capacity, albedo_textures, i, perlin, negative);
			if (k == -1)
			{
				float omega = 1 - cos_a_max;
				float3 c = light.emission * pow(dot(shadow_ray.d, res.normal), 2) * omega * path_capacity;
				result += c;
			}
		}
	}
	return (result);
}

float3			get_paralel_light(__constant t_object *objects, __constant t_scene *scene, t_intersection res, __global float3 *albedo_textures, __global float *perlin, __constant t_object *n_objects)
{
	float3 result = 0;
	float dp = dot(scene->parallel_dir, res.normal);
	if (dp > 0)
		return (result);
	else
		dp = -dp;
	t_ray shadow_ray;
	shadow_ray.d = scene->parallel_dir;
	shadow_ray.o = res.hit_point + shadow_ray.d * 0.01f;
	shadow_ray.t = 0.0f;
	float3 path_capacity;
	t_negative negative = get_negative_range(n_objects, scene, shadow_ray);
	if (intersect_in_range(objects, scene, shadow_ray, INFIN, res, &path_capacity, albedo_textures, -1, perlin, negative) == -1)
		result = scene->parallel_emis * dp * path_capacity;
	return (result);
}

float3			get_spotlight_light(__constant t_object *objects, __constant t_scene *scene, __constant t_spotlight *spotlights, unsigned int *seed0, unsigned int *seed1, t_intersection res, __global float3 *albedo_textures, __global float *perlin, __constant t_object *n_objects)
{
	float3			result = 0;
	t_spotlight		sp;
	t_ray			ray;

	int i = -1;
	while (++i < scene->amount_of_spotlights)
	{
		sp = spotlights[i];

		if (dot(res.normal, sp.dir) >= 0.0f)
			continue ;

		float3 sp_pos = sp.pos;
		float r1 = 2.f * MY_PI * get_random(seed0, seed1);
		float r2 = get_random(seed0, seed1);
		float r2s = sqrt(r2);
		sp_pos = sp.u * cos(r1) * r2s + sp.v * sin(r1) * r2s + sp_pos;



		float3 Ph_p_vec = sp_pos - res.hit_point;
		float t = dot(-1 * Ph_p_vec, sp.dir);
		if (t < EPS)
			continue ;
		ray.d = fast_normalize(Ph_p_vec);
		ray.o = res.hit_point;
		ray.t = 0.0f;
		float3 path_capacity;
		t_negative negative = get_negative_range(n_objects, scene, ray);
		if (intersect_in_range(objects, scene, ray, length(Ph_p_vec) - 1.0f,
							   res, &path_capacity, albedo_textures,
							   -1, perlin, negative) != -1)
			continue ;

		float3 O = sp_pos + sp.dir * t;
		float Oh_p = distance(O, res.hit_point);
		float alpha = atan2(Oh_p, t);
		if (alpha < sp.alpha)
			result += sp.emission * pow(dot(sp.dir, res.normal), 2) * pow(1 - alpha / sp.alpha, 4) * path_capacity;
	}
	return (result);
}

static void		get_tex_coord(int *tx, int *ty,
								float3 hit_point,
								float3 normal,
							  t_object object,
								float3 point1,
								   int tex_size)
{
	if (object.type == SPHERE)
	{
		*tx = (int)(atan2(normal.y, normal.x) / (2.0f * MY_PI) * (float)(tex_size)) / object.tex_scale;
		*ty = (int)(acos(normal.z) * I_MY_PI * (float)(tex_size)) + ((object.albedo_n == PERLIN) ? 0 : tex_size * object.albedo_n);
	}
	else if (object.type == PLANE)
	{
		float3 p = hit_point - point1;
		float px = dot(p, object.edge0);
		float py = dot(p, object.edge1);
		*tx = abs((int)((int)(px * object.tex_scale) % tex_size));
		*ty = abs((int)((int)(py * object.tex_scale) % tex_size)) + ((object.albedo_n == PERLIN) ? 0 : tex_size * object.albedo_n);
	}
	else if (object.type == CYLINDER)
	{
		float x = dot(normal, object.edge0);
		float y = dot(normal, object.edge1);
		float3 vec = hit_point - point1;
		if (fast_length(vec) <= object.radius + 0.005f || fast_length(vec - object.dir * object.top) <= object.radius + 0.005f)
		{
			float3 kek = vec / object.radius * 0.5f;
			*tx = (int)(((dot(kek, object.edge0) + 0.5f) * (float)(tex_size)) / object.tex_scale) % tex_size;
			*ty = (int)(((dot(kek, object.edge1) + 0.5f) * (float)(tex_size)) / object.tex_scale) % tex_size + ((object.albedo_n == PERLIN) ? 0 : tex_size * object.albedo_n);		
		}
		else
		{	
			float3 OO = vec - normal * object.radius;
			*tx = (int)(atan2(x, y) / (2.0f * MY_PI) * (float)(tex_size)) / object.tex_scale;
			*ty = (int)(fast_length(OO) / object.top * (float)(tex_size)) + ((object.albedo_n == PERLIN) ? 0 : tex_size * object.albedo_n);
		}
	}
	else if (object.type == DISK)
	{
		float3 kek = (hit_point - point1) / object.radius * 0.5f;
		*tx = (int)(((dot(kek, object.edge0) + 0.5f) * (float)(tex_size)) * 2 / object.tex_scale) % tex_size;
		*ty = (int)(((dot(kek, object.edge1) + 0.5f) * (float)(tex_size)) * 2 / object.tex_scale) % tex_size + ((object.albedo_n == PERLIN) ? 0 : tex_size * object.albedo_n);
	}
	*tx += object.tex_shift * tex_size;
	if (*tx > tex_size)
		*tx -= tex_size;
}

static float3	get_absorption(t_object object, float3 hit_point, float3 normal, __global float3 *albedo_textures, __global float *perlin)
{
	int tx, ty;

	if (object.albedo_n == PERLIN)
	{
		float p = perlin[tx + ty * 800];
		return (((float3)(1, 1, 1) - (float3)(p, p, p)) / 100);
	}

	get_tex_coord(&tx, &ty, hit_point, normal, object, object.point1, 2048);
	if (object.albedo_n == NORMAL || object.albedo_n == CHECKERBOARD)
	{
		if (object.albedo_n == NORMAL)
			return (((float3)(1, 1, 1) - (float3)(pow(normal.x, 2), pow(normal.y, 2), pow(normal.z, 2))) / 100);
		else
			return (((float3)(1, 1, 1) - (float3)(1, 1, 1) * pow(sin(50 * normal.x) * sin(50 * normal.y) * sin(50 * normal.z), 2)) / 100);
	}
	else
		return (((float3)(1, 1, 1) - albedo_textures[tx + ty * 2048]) / 100);
}

int				intersect_in_range(__constant t_object *objects, __constant t_scene *scene, t_ray r, const float maxt, t_intersection issect, float3 *path_capacity, __global float3 *albedo_textures, int k, __global float *perlin, t_negative negative)
{
	*path_capacity = 1;

	float3 normal_tmp_, hit_point_tmp_;
	int i = -1, n;
	while (++i < scene->amount_of_objects)
	{
		if (i == k)
			continue ;
		if (objects[i].material == TRANSPARENT)
		{
			float3 normal, hit_point;
			float t1 = intersect((t_object)(objects[i]), r, &normal, &hit_point, negative, &n);
			if (t1 > EPS && t1 < maxt)
			{
				t_ray tmp_ray = r;
				tmp_ray.o += (t1 + EPS) * r.d;
				float path_len = intersect((t_object)(objects[i]), tmp_ray, &normal_tmp_, &hit_point_tmp_, negative, &n);
				if (path_len > EPS)
				{
					float3 k;
					if (objects[i].albedo_n == -1)
						k = objects[i].absorption;
					else
						k = get_absorption((t_object)objects[i], hit_point, normal, albedo_textures, perlin);
					path_len = (path_len > maxt - t1) ? maxt - t1 : path_len;
					*path_capacity *= (float3)(exp(-1 * k.x * path_len), exp(-1 * k.y * path_len), exp(-1 * k.z * path_len)) * objects[i].color;
				}
			}
		}
		else
		{
			float t = intersect((t_object)(objects[i]), r, &normal_tmp_, &hit_point_tmp_, negative, &n);
			if ((t > EPS) && (t < maxt) && !lean_in_range(negative.range, t))
				return i;
		}
	}
	return (-1);
}

t_negative		range_cylinder(t_object object, t_ray ray)
{
	t_negative	result;
	result.range.x = -INFIN;
	result.range.y = 0.0f;
	result.hit_point = 0;
	result.normal = (float3)(1, 0, 0);

	t_quad		q;
	q.x = ray.o - object.point1;
	q.a = 1.0f - pow(dot(ray.d, object.dir), 2);
	q.b = 2.0 * (dot(ray.d, q.x) - dot(ray.d, object.dir) * dot(q.x, object.dir));
	q.c = dot(q.x, q.x) - pow(dot(q.x, object.dir), 2) - object.radius * object.radius;

	if (!solve_quadratic(&q))
		return result;

	q.t1 = (!check_for_m_cyl(ray, object, q, q.t1)) ? -1 : q.t1;
	q.t2 = (!check_for_m_cyl(ray, object, q, q.t2)) ? -1 : q.t2;

	float m = (dot(object.dir, ray.d) > 0) ? 0 : object.top;

	t_object disk;
	disk.point1 = object.point1 + object.dir * m;
	disk.n = (m > EPS) ? -object.dir : object.dir;
	disk.radius = object.radius;
	float3	closer_normal, closer_hp;
	float t1 = intersect_disk(disk, ray, &closer_normal, &closer_hp);

	disk.point1 = object.point1 + object.dir * ((m > EPS) ? 0 : object.top);
	disk.n = (m > EPS) ? object.dir : -object.dir;
	float3	further_normal, further_hp;
	float t2 = intersect_disk(disk, ray, &further_normal, &further_hp);

	if (t1 < EPS && t2 < EPS && q.t1 < EPS && q.t2 < EPS)
	{
		result.range.x = 0;
		result.range.y = EPS;
		return result;
	}
	else if (t1 < EPS && t2 < EPS && q.t1 > EPS && q.t2 > EPS)
	{
		result.range.x = min(q.t1, q.t2);
		result.range.y = max(q.t1, q.t2);
		result.hit_point = ray.o + ray.d * result.range.y;
		float tmp = dot(object.dir, object.point1 - result.hit_point);
		float3 h_p = object.dir * tmp;
		h_p = object.point1 - h_p;
		result.normal = fast_normalize(h_p - result.hit_point);
		return result;
	}
	else if (t1 > EPS && t2 > EPS) // II
	{
		result.range.x = t1;
		result.range.y = t2;
		result.normal = further_normal;
		result.hit_point = further_hp;
		return result;
	}
	else if (q.t2 > EPS && q.t1 < EPS) // III
	{
		result.range.x = t1;
		result.range.y = q.t2;
		result.hit_point = ray.o + ray.d * q.t2;
		float tmp = dot(object.dir, object.point1 - result.hit_point);
		float3 h_p = object.dir * tmp;
		h_p = object.point1 - h_p;
		result.normal = fast_normalize(h_p - result.hit_point);
		return result;
	}
	else if (q.t2 < EPS && q.t1 > EPS) // IV
	{
		result.range.x = q.t1;
		result.range.y = t2;
		result.normal = further_normal;
		result.hit_point = further_hp;
		return result;
	}
	else if (t1 < EPS && t2 > EPS)
	{
		result.range.x = 0;
		result.range.y = t2;
		result.normal = further_normal;
		result.hit_point = further_hp;
		return result;
	}
	else if (q.t1 > EPS && q.t2 > EPS)
	{
		result.range.x = min(q.t1, q.t2);
		result.range.y = max(q.t1, q.t2);
		result.hit_point = ray.o + ray.d * result.range.y;
		float tmp = dot(object.dir, object.point1 - result.hit_point);
		float3 h_p = object.dir * tmp;
		h_p = object.point1 - h_p;
		result.normal = fast_normalize(h_p - result.hit_point);
		return result;
	}
	else if (t1 > EPS && t2 < EPS)
	{
		result.range.x = t1;
		result.range.y = q.t2;
		result.hit_point = ray.o + ray.d * q.t2;
		float tmp = dot(object.dir, object.point1 - result.hit_point);
		float3 h_p = object.dir * tmp;
		h_p = object.point1 - h_p;
		result.normal = fast_normalize(h_p - result.hit_point);
		return result;
	}
	return result;
}

t_negative		range_sphere(t_object object, t_ray ray)
{
	t_negative	result;
	result.range.x = -INFIN;
	result.range.y = 0.0f;
	result.hit_point = 0;
	result.normal = (float3)(1, 0, 0);

	t_quad q;
	q.a = 1.0f;
	q.b = 2.0f * dot(ray.d, ray.o - object.point1);
	q.c = object.c2 + dot(ray.o, ray.o) - 2 * dot(ray.o, object.point1) - object.radius2;
	if (!solve_quadratic(&q))
		return result;
	if (q.t1 < EPS && q.t2 < EPS)
		return result;
	else if (q.t1 > EPS && q.t2 > EPS)
	{
		result.range.x = q.t1;
		result.range.y = q.t2;
		result.hit_point = ray.o + ray.d * q.t2;
		result.normal = fast_normalize(object.point1 - result.hit_point);
		return result;
	}
	else if (q.t1 < EPS && q.t2 > EPS)
	{
		result.range.x = 0;
		result.range.y = q.t2;
		result.hit_point = ray.o + ray.d * q.t2;
		result.normal = fast_normalize(object.point1 - result.hit_point);
		return result;
	}
	else
		return result;
}

t_negative		get_negative_range(__constant t_object *n_objects, __constant t_scene *scene, t_ray ray)
{
	t_negative	result;

	result.range.x = -INFIN;
	result.range.y = 0.0f;
	if (scene->amount_of_negative_objects == 0)
		return result;
	t_object object = (t_object)(*n_objects);
	if (object.type == CYLINDER)
		return range_cylinder(object, ray);
	else if (object.type == SPHERE)
		return range_sphere(object, ray);
	else
		return result;
}

t_intersection	get_intersect(__constant t_object *objects,
							   __constant t_scene *scene,
							   				t_ray ray,
									 unsigned int *seed0, unsigned int *seed1,
						   __constant t_spotlight *spotlights,
						   			   t_negative negative)
{
	t_intersection	result;

	float		min_dist = INFIN, t;
	float3		hit_point_tmp, normal_tmp;
	int			k = -1;
	result.took_place = -1;
	int n;

	while (++k < scene->amount_of_objects)
	{
		t = intersect((t_object)(objects[k]), ray, &normal_tmp, &hit_point_tmp, negative, &n);
		if (t > EPS && t < min_dist)
		{
			result.normal = normal_tmp;
			result.hit_point = hit_point_tmp;
			result.took_place = k;
			result.negative = n;
			min_dist = t;
		}
	}
	if (result.took_place == -1)
		return (result);
	result.color = objects[result.took_place].color;
	if (scene->light_on == 0)
		return (result);
	result.u = fast_normalize(cross((fabs(result.normal.x) > 1e-6) ? (float3)(0.f, 1.f, 0.f) : (float3)(1.f, 0.f, 0.f), result.normal));
	result.v = fast_normalize(cross(result.normal, result.u));
	return (result);
}

float3			get_environment_radiance(__global float3 *environment_map,
								  __constant t_scene *scene,
								  			   t_ray ray,
										  t_negative neg)
{
	float3 normal;
	t_quad q;
	q.a = 1.0f;
	q.b = 2.0f * dot(ray.d, ray.o);
	q.c = dot(ray.o, ray.o) - 1e30f;
	solve_quadratic(&q);

	normal = fast_normalize(ray.o + ray.d * q.t2);
	int tx = (int)(atan2(normal.y, normal.x) * (float)(scene->env_map_w) / (2.0f * MY_PI));
	int ty = (int)(acos(normal.z) * I_MY_PI * (float)(scene->env_map_h));
	int i = tx + ty * scene->env_map_w;
	if (i >= scene->env_map_h * scene->env_map_w)
		i = scene->env_map_h * scene->env_map_w - 1;
	else if (i < 0)
		i = 0;
	return environment_map[i];
}

float3		get_environment_light(__constant t_object *objects,
									  __global float3 *environment_map,
								   __constant t_scene *scene,
										 unsigned int *seed0, unsigned int *seed1,
									   t_intersection issect,
								  __constant t_object *n_objects,
									  __global float3 *albedo_textures,
									   __global float *perlin)
{
	float3 result = 0;
	t_ray ray;
	// float r1 = 2.f * MY_PI * get_random(seed0, seed1);
	// float r2 = get_random(seed0, seed1);
	// float r2s = sqrt(r2);
	// ray.d = fast_normalize(issect.u * cos(r1) * r2s + issect.v * sin(r1) * r2s + issect.normal * sqrt(1 - r2));

	int i = -1;
	int N = 1;
	while (++i < N)
	{
		float phi = get_random(seed0, seed1) * TWO_PI;
		float z = get_random(seed0, seed1);
		float zs = sqrt(1 - z * z);
		ray.d = fast_normalize(issect.u * zs * cos(phi) + issect.v * zs * sin(phi) + issect.normal * z);
		ray.o = issect.hit_point + ray.d * 0.01f;

		t_negative neg = get_negative_range(n_objects, scene, ray);

		float3 path_capacity;
		int k = intersect_in_range(objects, scene, ray, INFIN, issect, &path_capacity, albedo_textures, -1, perlin, neg);

		if (k == -1)
			result += get_environment_radiance(environment_map, scene, ray, neg) * dot(ray.d, issect.normal) * path_capacity;
	}
	return result / N;
}

__kernel void		compute_prime_ray(__global t_ray *output,
								  __constant t_scene *scene,
								 __constant t_camera *camera,
							   __global unsigned int *seed,
												 int current_sample,
									__global t_state *states)
{
	const int		id = get_global_id(0);
	int				gid2 = id * 2;
	unsigned int	seed0 = seed[gid2];
	unsigned int	seed1 = seed[gid2 + 1];

	int				x = id % scene->image_width;
	int				y = id / scene->image_width + scene->node_id * scene->image_height / scene->amount_of_nodes;

	float r1 = get_random(&seed0, &seed1) - .5f;
	float r2 = get_random(&seed0, &seed1) - .5f;
	float xx = 2.0f * ((x + r1) * camera->inv_width - .5f) * camera->aspectratio;
	float yy = 2.0f * (.5f - (y + r2) * camera->inv_height);

	// float Px = (2 * ((x + 0.5) / imageWidth) - 1) * a->camera->angle * a->scene->image_width / (float)a->scene->image_height;
	// float Py = (1 - 2 * ((y + 0.5) / imageHeight) * a->camera->angle;

	states[id].rad = (float3)(0.0f, 0.0f, 0.0f);
	states[id].path_capacity = (float3)(1.0f, 1.0f, 1.0f);
	states[id].is_survive = 1;
	states[id].through_transparent = 0;
	states[id].current_absorption = (float3)(0.0f, 0.0f, 0.0f);
	states[id].specular_bounce = 1;
	states[id].glossy_bounce = 0;

	t_ray ray;
	ray.d = 0;
	ray.o = camera->pos;
	ray.t = camera->t * get_random(&seed0, &seed1);

	if (scene->mode == STANDARD)
		ray.d = fast_normalize(camera->angle * (camera->right * xx + camera->up * yy) + camera->dir);
	else if (scene->mode == DOF)
	{
		t_ray tmp_ray;
		tmp_ray.d = fast_normalize(camera->angle * (camera->right * xx + camera->up * yy) + camera->dir);
		tmp_ray.o = camera->pos;
		float rand1 = my_clamp(get_random(&seed0, &seed1));
		float rand2 = my_clamp(get_random(&seed0, &seed1));
		float3 offset = camera->aperture * (rand1 * cos((float)TWO_PI * rand2) * camera->right + rand1 * sin((float)TWO_PI * rand2) * camera->up);
		float3 focalPlaneIntersection = tmp_ray.o + tmp_ray.d * camera->focal_length / dot(camera->dir, tmp_ray.d);
		ray.o += offset;
		ray.d = fast_normalize(focalPlaneIntersection - ray.o);
	}
	else if (scene->mode == FISHEYE)
	{
		float x2 = xx * xx;
		float r = sqrt(x2 + yy * yy);
		if (r > 1.0f)
			states[id].is_survive = 0;
		else
		{
			float nr = sqrt(1.0f - r * r);
			nr = (r + (1.0f - nr)) * 0.5f;
			if (nr > 1.0f)
				states[id].is_survive = 0;
			else
			{
				float theta = atan2(xx, yy);
				float nx = nr * cos(theta);
				float ny = nr * sin(theta);
				ray.d = fast_normalize(camera->right * ny + camera->up * nx + camera->dir);
			}
		}
	}

	output[id] = ray;

	seed[gid2] = seed0;
	seed[gid2 + 1] = seed1;
}

__kernel void		generate_depth_map(__global float *depth_map,
									   __global t_ray *current_rays,
								   __constant t_scene *scene,
								  __constant t_object *objects,
								  __constant t_object *n_objects)
{
	const int	id = get_global_id(0);
	
	int			k = -1;
	float		min_dist = INFIN, t;
	float3		hit_point_tmp, normal_tmp;
	t_ray ray = current_rays[id];
	t_negative neg = get_negative_range(n_objects, scene, ray);
	int n;
	while (++k < scene->amount_of_objects)
	{
		t = intersect((t_object)(objects[k]), ray, &normal_tmp, &hit_point_tmp, neg, &n);
		if (t > EPS && t < min_dist)
			min_dist = t;
	}
	depth_map[id] = min_dist;
}

__kernel void		compute_intersection(__global t_intersection *intersection,
											  __constant t_scene *scene,
											 __constant t_object *objects,
												  __global t_ray *current_rays,
										  __constant t_spotlight *spotlights,
										   __global unsigned int *seed,
											 __constant t_object *n_objects,
												__global t_state *states,
												 __global float3 *environment_map)
{
	const int	id = get_global_id(0);
	const int	gid2 = id * 2;

	t_state state = states[id];

	if (state.is_survive == 0)
		return ;

	unsigned int seed0 = seed[gid2];
	unsigned int seed1 = seed[gid2 + 1];

	t_ray ray = current_rays[id];

	t_negative neg = get_negative_range(n_objects, scene, ray);
	intersection[id] = get_intersect(objects, scene, ray, &seed0, &seed1, spotlights, neg);

	if (scene->env_map && intersection[id].took_place == -1)
		states[id].rad += state.path_capacity * get_environment_radiance(environment_map, scene, ray, neg);

	seed[gid2] = seed0;
	seed[gid2 + 1] = seed1;
}

__kernel void		get_texturing(__global t_intersection *intersection,
									   __constant t_scene *scene,
									  __constant t_object *objects,
										  __global float3 *albedo_textures,
										  __global float3 *normal_textures,
										   __global float *perlin)
{
	const int	id = get_global_id(0);

	if (intersection[id].took_place == -1)
		return ;
	if (intersection[id].negative == 1)
	{
		// intersection[id].color = (float3)(pow(intersection[id].normal.x, 2), pow(intersection[id].normal.y, 2), pow(intersection[id].normal.z, 2));
		intersection[id].color = objects[intersection[id].took_place].color;
		return ;
	}

	t_object	object = (t_object)objects[intersection[id].took_place];

	if (object.albedo_n == -1)
	{
		if (object.material == TRANSPARENT)
			intersection[id].color = object.absorption;
		return ;
	}

	t_intersection	issect = intersection[id];
	float3 point1 = object.point1;
	int tx, ty;
	if (object.type == SPHERE || object.type == PLANE || object.type == CYLINDER || object.type == DISK || (object.type == TORUS && object.albedo_n == NORMAL))
	{
		if (object.albedo_n == PERLIN)
			get_tex_coord(&tx, &ty, issect.hit_point, issect.normal, object, point1, 800);
		else
			get_tex_coord(&tx, &ty, issect.hit_point, issect.normal, object, point1, 2048);
	}
	else
	{
		if (object.material == TRANSPARENT)
			intersection[id].color = object.absorption;
		return ;
	}

	if (object.albedo_n == PERLIN)
	{
		float p = perlin[tx + ty * 800];
		intersection[id].color = (float3)(p, p, p) * object.color;
		if (object.material == TRANSPARENT)
			intersection[id].color /= 100;
	}
	else if (object.albedo_n == TRUE_CHECKER)
	{
		float3 p = issect.hit_point - object.point1;
		float px = dot(p, object.edge0);
		float py = dot(p, object.edge1);
		int i = (px > 0) ? 1 : 0,
			j = (py < 0) ? 1 : 0;
		int len = 2048 / 32;
		if (((ty + 1) / len + j) % 2 == 0)
		{
			if ((tx / len + i) % 2 == 1)
				intersection[id].color = (float3)(1, 1, 1);
			else
				intersection[id].color = (float3)(0.5, 0.3, 0.7);
		}
		else
		{
			if ((tx / len + i) % 2 == 0)
				intersection[id].color = (float3)(1, 1, 1);
			else
				intersection[id].color = (float3)(0.3, 0.7, 0.5);
		}
	}
	else if (object.albedo_n == NORMAL || object.albedo_n == CHECKERBOARD)
	{
		float k2;
		k2 = pow(sin(intersection[id].normal.x * 7.0f * MY_PI), 2);
		if (object.material != TRANSPARENT)
		{
			if (object.albedo_n == NORMAL)
			{
				intersection[id].color = (float3)(pow(intersection[id].normal.x, 2), pow(intersection[id].normal.y, 2), pow(intersection[id].normal.z, 2));
				intersection[id].normal = fast_normalize(issect.u * k2 + issect.v + issect.normal * sqrt(1 - k2));
				intersection[id].u = fast_normalize(cross((fabs(intersection[id].normal.x) > 1e-6) ? (float3)(0.f, 1.f, 0.f) : (float3)(1.f, 0.f, 0.f), intersection[id].normal));
				intersection[id].v = fast_normalize(cross(intersection[id].normal, intersection[id].u));
			}
			else
				intersection[id].color = object.color * pow(sin(50 * intersection[id].normal.x) * sin(50 * intersection[id].normal.y) * sin(50 * intersection[id].normal.z), 2);
		}
		else
		{
			if (object.albedo_n == NORMAL)
			{
				intersection[id].color = (float3)(1, 1, 1) - (float3)(pow(intersection[id].normal.x, 2), pow(intersection[id].normal.y, 2), pow(intersection[id].normal.z, 2));
				intersection[id].normal = fast_normalize(issect.u * k2 + issect.v + issect.normal * sqrt(1 - k2));
				intersection[id].u = fast_normalize(cross((fabs(intersection[id].normal.x) > 1e-6) ? (float3)(0.f, 1.f, 0.f) : (float3)(1.f, 0.f, 0.f), intersection[id].normal));
				intersection[id].v = fast_normalize(cross(intersection[id].normal, intersection[id].u));
			}
			else
				intersection[id].color = (float3)(1, 1, 1) - object.color * pow(sin(50 * intersection[id].normal.x) * sin(50 * intersection[id].normal.y) * sin(50 * intersection[id].normal.z), 2);
				intersection[id].color /= 100;
		}
	}
	else
	{
		if (object.material == TRANSPARENT)
			intersection[id].color = ((float3)(1, 1, 1) - albedo_textures[tx + ty * 2048]) / 250;
		else
		{
			float3 nl_m = normal_textures[tx + ty * 2048];
			intersection[id].normal = fast_normalize(issect.u * nl_m.x + issect.v * nl_m.y + issect.normal * nl_m.z);
			intersection[id].u = fast_normalize(cross((fabs(intersection[id].normal.x) > 1e-6) ? (float3)(0.f, 1.f, 0.f) : (float3)(1.f, 0.f, 0.f), intersection[id].normal));
			intersection[id].v = fast_normalize(cross(intersection[id].normal, intersection[id].u));
			intersection[id].color = albedo_textures[tx + ty * 2048];
		}
		
	}
}

__kernel void		get_radiance(__global t_intersection *intersection,
									  __constant t_scene *scene,
									 __constant t_object *objects,
								  __constant t_spotlight *spotlights,
								   __global unsigned int *seed,
										 __global float3 *albedo_textures,
										  __global float *perlin,
									 __constant t_object *n_objects,
									 	 __global float3 *environment_map)
{
	const int	id = get_global_id(0);
	const int	gid2 = id * 2;

	unsigned int seed0 = seed[gid2];
	unsigned int seed1 = seed[gid2 + 1];

	if (intersection[id].took_place != -1 && objects[intersection[id].took_place].kd > 0.05f)
	{
		float3 Ld = get_direct_light(objects, scene, &seed0, &seed1, (t_intersection)intersection[id], albedo_textures, perlin, n_objects);
		float3 Lp = (scene->parallel_light) ? get_paralel_light(objects, scene, (t_intersection)intersection[id], albedo_textures, perlin, n_objects) : 0;
		float3 Ls = (scene->spotlight) ? get_spotlight_light(objects, scene, spotlights, &seed0, &seed1, (t_intersection)intersection[id], albedo_textures, perlin, n_objects) : 0;
		float3 Le = (scene->env_map && scene->radiance_env_map) ? get_environment_light(objects, environment_map, scene, &seed0, &seed1, (t_intersection)intersection[id], n_objects, albedo_textures, perlin) : 0;
		if (isnan_float3(Ld) || isnan_float3(Lp) || isnan_float3(Ls) || isnan_float3(Le))
			intersection[id].radiance = 0;
		else
			intersection[id].radiance = Ld + Ls + Lp + Le + scene->ambient;
		
		seed[gid2] = seed0;
		seed[gid2 + 1] = seed1;
	}
	else if (!scene->env_map)
		intersection[id].radiance = scene->ambient;
}

__kernel void		do_trace(__global t_state *states,
					  __global t_intersection *intersections,
						  __constant t_object *objects,
						   __constant t_scene *scene,
							   __global t_ray *current_rays,
						__global unsigned int *seed)
{
	const int	id = get_global_id(0);

	if (!states[id].is_survive)
		return ;

	t_intersection issect = intersections[id];

	if (issect.took_place == -1)
	{
		states[id].is_survive = 0;
		return ;
	}

	t_object object = objects[issect.took_place];

	if (scene->light_on == 0)
	{
		states[id].rad = issect.color;
		return ;
	}

	int gid2 = id * 2;
	unsigned int seed0 = seed[gid2];
	unsigned int seed1 = seed[gid2 + 1];

	float dp = dot(issect.normal, current_rays[id].d);
	issect.normal = (dp > 0) ? -1 * issect.normal : issect.normal;

	if (object.material == DIFF)
	{
		states[id].specular_bounce = 0;
		states[id].path_capacity *= issect.color;

		if (states[id].through_transparent) {
			float3 k = states[id].current_absorption;
			states[id].through_transparent = 0;
			float path_len = fast_distance(current_rays[id].o, issect.hit_point);
			states[id].path_capacity *= (float3)(exp(-1 * k.x * path_len), exp(-1 * k.y * path_len), exp(-1 * k.z * path_len));
		}
		states[id].rad += states[id].path_capacity * (issect.radiance + clamp_vec(object.emission));

		if (!scene->indirect_light)
			states[id].is_survive = 0;
		else 
		{
			float r1 = 2.f * MY_PI * get_random(&seed0, &seed1);
			float r2 = get_random(&seed0, &seed1);
			float r2s = sqrt(r2);

			current_rays[id].d = fast_normalize(issect.u * cos(r1) * r2s + issect.v * sin(r1) * r2s + issect.normal * sqrt(1 - r2));
			current_rays[id].o = issect.hit_point + current_rays[id].d * 0.01f;
			states[id].path_capacity *= dot(current_rays[id].d, issect.normal);
		}
	}
	else if (object.material == SPEC)
	{
		states[id].path_capacity *= issect.color;
		states[id].specular_bounce = 1;

		if (states[id].through_transparent) {
			float3 k = states[id].current_absorption;
			states[id].through_transparent = 0;
			float path_len = fast_distance(current_rays[id].o, issect.hit_point);
			states[id].path_capacity *= (float3)(exp(-1 * k.x * path_len), exp(-1 * k.y * path_len), exp(-1 * k.z * path_len));
		}
		if (object.kd > 0.051f)
		{
			states[id].rad += states[id].path_capacity * issect.radiance * object.kd;
			states[id].path_capacity *= (1.0f - object.kd);
		}
		current_rays[id].d = fast_normalize(current_rays[id].d - 2.f * dp * issect.normal);
		current_rays[id].o = issect.hit_point + current_rays[id].d * 0.01f;
	}
	else if (object.material == REFR)
	{
		states[id].path_capacity *= object.color;

		if (states[id].through_transparent) {
			float3 k = states[id].current_absorption;
			states[id].through_transparent = 0;
			float path_len = fast_distance(current_rays[id].o, issect.hit_point);
			states[id].path_capacity *= (float3)(exp(-1 * k.x * path_len), exp(-1 * k.y * path_len), exp(-1 * k.z * path_len));
		}
		states[id].specular_bounce = 1;

		t_ray refl_ray;
		refl_ray.d = fast_normalize(current_rays[id].d - 2.f * dp * issect.normal);
		refl_ray.o = issect.hit_point + refl_ray.d * 0.01f;
		refl_ray.t = current_rays[id].t;

		int into = (dp < 0);
		float nc = 1.f;
		float nt = object.refr_index;
		float nnt = into ? nc / nt : nt / nc;
		float ddn = into ? dp : -1 * dp;
		float cos2t = 1.f - nnt * nnt * (1.f - ddn * ddn);

		if (cos2t < 0.f) {
			current_rays[id] = refl_ray;
			seed[gid2] = seed0;
			seed[gid2 + 1] = seed1;
			return ;
		}

		float kk = into ? 1 : -1 * (ddn * nnt + sqrt(cos2t));
		float3 trans_dir = fast_normalize(nnt * current_rays[id].d - issect.normal * kk);

		float a = nt - nc;
		float b = nt + nc;
		float R0 = a * a / (b * b);
		float c = 1 - (into ? -ddn : (dot(trans_dir, issect.normal)));
		float Re = c;
		c *= c;
		c *= c;
		Re = R0 + (1 - R0) * Re * c;
		float Tr = 1.f - Re;
		float P = .25f + .5f * Re;
		float RP = Re / P;
		float TP = Tr / (1.f - P);

		if (object.kd > 0.051f)
		{
			states[id].rad += states[id].path_capacity * issect.radiance * object.kd;
			states[id].path_capacity *= 1.0f - object.kd;
		}

		if (get_random(&seed0, &seed1) < P) {
			states[id].path_capacity *= RP;
			current_rays[id] = refl_ray;
			return ;
		}
		else {
			states[id].path_capacity *= TP;
			current_rays[id].o = issect.hit_point + trans_dir * 0.1f;
			current_rays[id].d = trans_dir;
			return ;
		}
	}
	else if (object.material == GLOSSY)
	{
		states[id].path_capacity *= issect.color;
		states[id].specular_bounce = 0;
		states[id].glossy_bounce = 1;

		if (states[id].through_transparent) {
			states[id].through_transparent = 0;
			float path_len = fast_distance(current_rays[id].o, issect.hit_point);
			float3 k = states[id].current_absorption;
			states[id].path_capacity *= (float3)(exp(-1 * k.x * path_len), exp(-1 * k.y * path_len), exp(-1 * k.z * path_len));
		}
		if (object.kd > 0.051f)
		{
			states[id].rad += states[id].path_capacity * issect.radiance * object.kd;
			states[id].path_capacity *= (1.0f - object.kd);
		}

		t_ray	reflect_ray;
		reflect_ray.d = fast_normalize(current_rays[id].d - 2.f * dp * issect.normal);

		t_basis uv = get_basis_from_vec(reflect_ray.d);

		float r1 = 2.f * MY_PI * get_random(&seed0, &seed1);
		float r2 = object.glossiness * get_random(&seed0, &seed1);
		float r2s = sqrt(r2);

		current_rays[id].d = fast_normalize(reflect_ray.d + cos(r1) * r2s * uv.u + sin(r1) * r2s * uv.v);
		if (dot(current_rays[id].d, issect.normal) < 0)
			current_rays[id].d = fast_normalize(reflect_ray.d - cos(r1) * r2s * uv.u - sin(r1) * r2s * uv.v);

		current_rays[id].o = issect.hit_point + reflect_ray.d * 0.01f;
		states[id].path_capacity *= dot(issect.normal, current_rays[id].d) * pow(my_clamp(dot(reflect_ray.d, current_rays[id].d)), 2);
	}
	else if (object.material == GLOSSY_REFR)
	{
		states[id].path_capacity *= object.color;
		if (object.kd > 0.051f)
		{
			states[id].rad += states[id].path_capacity * issect.radiance * object.kd;
			states[id].path_capacity *= 1.0f - object.kd;
		}

		int into = (dp < 0);
		float nc = 1.f;
		float nt = object.refr_index;
		float nnt = into ? nc / nt : nt / nc;
		float ddn = into ? dp : -1 * dp;
		float cos2t = 1.f - nnt * nnt * (1.f - ddn * ddn);
		float kk = into ? 1 : -1 * (ddn * nnt + sqrt(cos2t));
		float3 trans_dir = fast_normalize(nnt * current_rays[id].d - issect.normal * kk);
		
		t_basis uv = get_basis_from_vec(trans_dir);

		float r1 = 2.f * MY_PI * get_random(&seed0, &seed1);
		float r2 = object.glossiness * get_random(&seed0, &seed1);
		float r2s = sqrt(r2);

		current_rays[id].d = fast_normalize(trans_dir + cos(r1) * r2s * uv.u + sin(r1) * r2s * uv.v);
		if (dot(current_rays[id].d, issect.normal) > 0)
			current_rays[id].d = fast_normalize(trans_dir - cos(r1) * r2s * uv.u - sin(r1) * r2s * uv.v);

		current_rays[id].o = issect.hit_point + current_rays[id].d * 0.01f;
	}
	else if (object.material == TRANSPARENT)
	{
		if (++states[id].through_transparent == 1)
			states[id].current_absorption = issect.color;
		else if (states[id].through_transparent == 2) {
			states[id].through_transparent = 0;
			float path_len = fast_distance(current_rays[id].o, issect.hit_point);
			float3 k = states[id].current_absorption;
			states[id].path_capacity *= (float3)(exp(-1 * k.x * path_len), exp(-1 * k.y * path_len), exp(-1 * k.z * path_len));
		}
		current_rays[id].o = issect.hit_point + current_rays[id].d * 0.01f;
	}
	else
		states[id].is_survive = 0;

	seed[gid2] = seed0;
	seed[gid2 + 1] = seed1;
}

static float3 Uncharted2Tonemap(float3 x)
{
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;

    return ((x * (A * x + C * B) + D * E) /
    	   (x * (A * x + B) + D * F))
    	   - E / F;
}

__kernel void		get_image(__global int *output,
					  __global t_state *states,
					__constant t_scene *scene,
					   __global float3 *colors,
								   int current_sample,
						__global float *depth_map)
{
	const int	id = get_global_id(0);

	float3 r = states[id].rad;
	if (current_sample == 0)
		colors[id] = r;
	else
	{
		float k1 = current_sample;
		float k2 = 1.f / (current_sample + 1.f);
		colors[id] *= k1;
		colors[id] += r;
		colors[id] *= k2;
	}

	if (isnan_float3(colors[id]))
		colors[id] = (float3)(1, 0, 0);

	float3 color = colors[id];
	if (scene->tone_mapper == UNCHARTED)
	{
		float crush = 0.05;
		float frange = 10;
		float exposure = 10;
		 
		color = smoothstep(crush, frange + crush, log2(1 + color * exposure));
		// color = Uncharted2Tonemap(color);
	}
	else if (scene->tone_mapper == STRONG)
		color = colors[id] / (colors[id] + (float3)(1, 1, 1));
	

	if (scene->visual_effect == SEPIA)
	{
		float3 tmp = (float3)(to_float(color.x), to_float(color.y), to_float(color.z));
		int tr = (int)(0.393f * tmp.x + 0.769f * tmp.y + 0.189f * tmp.z);
		int tg = (int)(0.349f * tmp.x + 0.686f * tmp.y + 0.168f * tmp.z);
		int tb = (int)(0.272f * tmp.x + 0.534f * tmp.y + 0.131f * tmp.z);
		tr = (tr > 255) ? 255 : tr;
		tg = (tg > 255) ? 255 : tg;
		tb = (tb > 255) ? 255 : tb;
		output[id] = tb + (tg << 8) + (tr << 16);
	}
	else if (scene->visual_effect == GREYSCALE)
	{
		float max_, min_;

		max_ = max(max(color.z, color.y), color.x);
		min_ = min(min(color.z, color.y), color.x);
		max_ = (max_ + min_) / 2.0f;
		output[id] = to_int(max_, scene->gamma) + (to_int(max_, scene->gamma) << 8) + (to_int(max_, scene->gamma) << 16);
	}
	else if (scene->visual_effect == FOG)
	{
		color = (color + (float3)(depth_map[id], depth_map[id], depth_map[id]) * 0.25f) * 0.8f;
		output[id] = to_int(color.z, scene->gamma) + (to_int(color.y, scene->gamma) << 8) + (to_int(color.x, scene->gamma) << 16);
	}
	else
		output[id] = to_int(color.z, scene->gamma) + (to_int(color.y, scene->gamma) << 8) + (to_int(color.x, scene->gamma) << 16);
}
