$input a_position
$output v_normal, v_tangent

// Implementation of Sean O'Neil's atmospheric shader
// See atmospheric_functions.shh for more details

#include <bgfx_shader.shh>
#include <atmospheric_functions.shh> 

// Uniforms
uniform vec4 u_sunDirection; 		// Sun vector in world. Normaised direction to it.
uniform vec4 u_worldPosAndSize; 	// The position and size of the world being rendered. (x,y,z) = position of the world in model space, w = world radius


void main() {
	float fInnerRadius = u_worldPosAndSize.w;     		// The inner (planetary) radius
	float fOuterRadius = (1.0/DRADIUS) * fInnerRadius;	// The outer (atmosphere) radius
	v_normal = mul(u_modelView, vec4(0.0,0.0,0.0,1.0)).xyz; // Exporting v3Origin -- The position of this relative to the camera
	v_tangent = mul(u_modelView, vec4(a_position.xyz * fOuterRadius, 1.0)).xyz; // Exporting v3Pos -- vertex position. Here we're projecting a unit sphere coordinate to a planet's surface

	gl_Position = mul(u_modelViewProj, vec4(a_position*fOuterRadius, 1.0) ); 
	}

