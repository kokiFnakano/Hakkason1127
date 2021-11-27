

class vec4
{
public:
	double x;
	double y;
	double z;
	double a;

	double mag();
	static double dist(vec4 from, vec4 to);
	void set(vec4 v);

	void set(float x, float y, float z, float a);

	void mult_self(float v);
	void add_self(vec4 v);


	static vec4 sub(vec4 v1, vec4 v2);
	static vec4 add(vec4 v1, vec4 v2);
	static vec4 mult(vec4 v1, vec4 v2);

	vec4();
	vec4(float X, float Y, float Z, float A);


	static double tri_size(vec4 t1, vec4 t2, vec4 t3);


	static vec4 zero();
	static vec4 one();

	static double dot(vec4 v1,vec4 v2);
	static vec4 normal(vec4 v1, vec4 v2);
	
	static vec4 lookat(vec4 from, vec4 to);
	static vec4 normalize(vec4 tgt);
	
	void printv(int x, int y,const char* st);
	
	vec4 operator* (const vec4& v);
	vec4 operator/ (const float& v);
	void operator*= (const double& v);
	void operator*= (const vec4& v);
	vec4 operator+ (const vec4& v);
	vec4 operator* (const double& v);
	void operator+= (const vec4& v);
	
	vec4 operator- (const vec4& v);


	bool operator== (const vec4& v);
};




