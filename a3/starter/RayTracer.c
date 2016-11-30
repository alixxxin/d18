/*
  CSC D18 - RayTracer code - Fall 2016 - Assignment 3&4

  Written Dec. 9 2010 - Jan 20, 2011 by F. J. Estrada
  Freely distributable for adacemic purposes only.

  Uses Tom F. El-Maraghi's code for computing inverse
  matrices. You will need to compile together with
  svdDynamic.c

  You need to understand the code provided in
  this file, the corresponding header file, and the
  utils.c and utils.h files. Do not worry about
  svdDynamic.c, we need it only to compute
  inverse matrices.

  You only need to modify or add code in sections
  clearly marked "TO DO"
*/

#include "utils.h"

// A couple of global structures and data: An object list, a light list, and the
// maximum recursion depth
struct object3D *object_list;
struct pointLS *light_list;
int MAX_DEPTH;

void buildScene(void)
{
 // Sets up all objects in the scene. This involves creating each object,
 // defining the transformations needed to shape and position it as
 // desired, specifying the reflectance properties (albedos and colours)
 // and setting up textures where needed.
 // Light sources must be defined, positioned, and their colour defined.
 // All objects must be inserted in the object_list. All light sources
 // must be inserted in the light_list.
 //
 // To create hierarchical objects:
 //   Copy the transform matrix from the parent node to the child, and
 //   apply any required transformations afterwards.
 //
 // NOTE: After setting up the transformations for each object, don't
 //       forget to set up the inverse transform matrix!

 struct object3D *o;
 struct pointLS *l;
 struct point3D p;

 ///////////////////////////////////////
 // TO DO: For Assignment 3 you have to use
 //        the simple scene provided
 //        here, but for Assignment 4 you
 //        *MUST* define your own scene.
 //        Part of your mark will depend
 //        on how nice a scene you
 //        create. Use the simple scene
 //        provided as a sample of how to
 //        define and position objects.
 ///////////////////////////////////////

 // Simple scene for Assignment 3:
 // Insert a couple of objects. A plane and two spheres
 // with some transformations.


  o=newPlane(.5,.75,.35,.05,0.4,0.4,0.4,1,1,2);
  Scale(o,40,20,20);
  // RotateZ(o,-PI/1.5);
  Translate(o,0,12,15);
  // RotateX(o,PI/2.25);
  invert(&o->T[0][0],&o->Tinv[0][0]);
  loadTexture(o,"./mytex/blue_sky_background.ppm");
  // loadTexture(o,"./texture/landscape.ppm", 1, &texture_list);
  // loadTexture(o,"./texture/stone_normal.ppm", 2, &texture_list);
  insertObject(o,&object_list);


 // Let's add a plane
 // Note the parameters: ra, rd, rs, rg, R, G, B, alpha, r_index, and shinyness)
 o=newPlane(.5,.75,.75,.75,.55,.8,.75,1,1,2);	// Note the plane is highly-reflective (rs=rg=.75) so we
						// should see some reflections if all is done properly.
						// Colour is close to cyan, and currently the plane is
						// completely opaque (alpha=1). The refraction index is
						// meaningless since alpha=1
 Scale(o,12,6,1);				// Do a few transforms...
 // Scale(o, 0.8, 0.8, 0.8);
 // RotateZ(o,PI/1.20);
 RotateX(o,PI/2.25);
 // RotateY(o, PI/);
 Translate(o,0,-3,10);
 invert(&o->T[0][0],&o->Tinv[0][0]);		// Very important! compute
						// and store the inverse
						// transform for this object!
 loadTexture(o,"./mytex/pineapple.ppm");
 insertObject(o,&object_list);			// Insert into object list

 // o=newPlane(.5,.75,.75,.75,.1,.1,.1,0.1,1,2); // Note the plane is highly-reflective (rs=rg=.75) so we
 // Scale(o,11,5.5,5);       // Do a few transforms...
 // RotateX(o,PI/2.25);
 // // RotateY(o, PI/);
 // Translate(o,0,-2.5,10);
 // invert(&o->T[0][0],&o->Tinv[0][0]);    // Very important! compute
 //            // and store the inverse
 //            // transform for this object!
 // insertObject(o,&object_list);      // Insert into object list





  // o=newPlane(.5,.75,.35,.05,0.4,0.4,0.4,1,1,2);
  // Scale(o,40,20,20);
  // // RotateZ(o,-PI/1.5);
  // Translate(o,0,12,15);
  // invert(&o->T[0][0],&o->Tinv[0][0]);
  // loadTexture(o,"./mytex/blue_sky_background.ppm");
  // insertObject(o,&object_list);


 // Let's add a couple spheres
 o=newSphere(.05,.95,.35,.35,1,.25,.25,1,1,6);
 Scale(o,0.2,0.2,0.2);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateY(o,PI/2);
 Translate(o, -1.9, 0.6, 2);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/venmap.ppm");
 insertObject(o,&object_list);




 o=newSphere(.05,.95,.35,.35,1,.25,.25,1,1,6);
 Scale(o,0.2,0.2,0.2);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateY(o,PI/2);
 Translate(o, -4, 0.6, 2);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/venmap.ppm");
 insertObject(o,&object_list);




 o=newSphere(.05,.95,.35,.35,1,.25,.25,1,1,6);
 Scale(o,0.35,0.35,0.35);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateY(o,PI/2);
 Translate(o,-1.8,0.7,2.5);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/Mun1.ppm");
 insertObject(o,&object_list);

 o=newSphere(.05,.95,.35,.35,1,.25,.25,1,1,6);
 Scale(o,0.5,0.5,0.5);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateY(o,PI/2);
 Translate(o,-1.7,0.9,3);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/Pol1.ppm");
 insertObject(o,&object_list);


 o=newSphere(.05,.95,.35,.35,1,.25,.25,1,1,6);
 Scale(o,0.7,0.7,0.7);
 // Scale(o, 0.8, 0.8, 0.8);
 // RotateY(o,PI/2);
 Translate(o,-1.45,1.1,3.5);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/Vall1.ppm");
 insertObject(o,&object_list);


 // o=newSphere(.05,.95,.95,.75,.75,.95,.55,1,1,6);

 // // o=newPlane(.5,.75,.05,.05,.55,.8,.75,1,1,2); // Note the plane is highly-reflective (rs=rg=.75) so we
 // //            // should see some reflections if all is done properly.
 // //            // Colour is close to cyan, and currently the plane is
 // //            // completely opaque (alpha=1). The refraction index is
 // //            // meaningless since alpha=1
 // Scale(o,1.5,1.2,0.3);        // Do a few transforms...
 // // Scale(o, 0.8, 0.8, 0.8);
 // RotateZ(o,PI/1.20);
 // RotateX(o,PI/3.25);
 // Translate(o,1.75,1.5,5.0);
 // invert(&o->T[0][0],&o->Tinv[0][0]);    // Very important! compute
 //            // and store the inverse
 //            // transform for this object!
 // loadTexture(o,"./mytex/planets/ring.ppm");
 // insertObject(o,&object_list);      // Insert into object list


 // o=newSphere(.05,.95,.95,.75,.75,.95,.55,1,1,6);
 // Scale(o,2,1.2,0.4);
 // // Scale(o, 0.8, 0.8, 0.8);
 // RotateZ(o,PI/1.5);
 // RotateX(o, -PI/2);
 // RotateY(o, PI/5);
 // Translate(o,1.75,1.25,5.0);
 // invert(&o->T[0][0],&o->Tinv[0][0]);
 // loadTexture(o,"./mytex/planets/saturnmap.ppm");
 // insertObject(o,&object_list);


 o=newSphere(.05,.95,.95,.75,.75,.95,.55,1,1,6);
  Scale(o,1.6,1.6,1.6);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateZ(o,PI/1.5);
 Translate(o,-0.6,2,8.0);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/Eve1.ppm");

 insertObject(o,&object_list);


 o=newSphere(.05,.95,.95,.75,.75,.95,.55,1,1,6);
 Scale(o,1,1,1);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateZ(o,PI/1.5);
 Translate(o,1,1.65,6.0);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/Minmus1.ppm");

 insertObject(o,&object_list);



 o=newSphere(.05,.95,.95,.75,.75,.95,.55,1,1,6);
 Scale(o,1,1,1);
 // Scale(o, 0.8, 0.8, 0.8);
 RotateZ(o,PI/1.5);
 Translate(o,1.75,1.25,3.5);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o,"./mytex/planets/saturnmap.ppm");
 insertObject(o,&object_list);



  o=newSphere(.05,.25,.75,.95,1,1,1,0.3,1.5,3);
  Scale(o,1.5,1.5,1.5);
  Translate(o,2,-1,3.5);
 // Translate(o,2,1.25,3.5);

  invert(&o->T[0][0],&o->Tinv[0][0]);
  insertObject(o,&object_list);



  // o=newPlane(.5,.75,.35,.05,0.4,0.4,0.4,1,1,2);
  // Scale(o,40,20,20);
  // // RotateZ(o,-PI/1.5);
  // Translate(o,0,12,15);
  // invert(&o->T[0][0],&o->Tinv[0][0]);
  // loadTexture(o,"./texture/starry_night.ppm");
  // insertObject(o,&object_list);



 // Insert a single point light source.
 // p.px=0;
 // p.py=15.5;
 // p.pz=-5.5;
 // p.pw=1;
 // l=newPLS(&p,1,1,1);//.75,.75,.75);
 // insertPLS(l,&light_list);

  addAreaLight(5, 3, 0, -1, 1,
             5, 25.5,-3.5, 5,7,
             .05, .05, .05,
             &object_list, &light_list);

 // End of simple scene for Assignment 3
 // Keep in mind that you can define new types of objects such as cylinders and parametric surfaces,
 // or, you can create code to handle arbitrary triangles and then define objects as surface meshes.
 //
 // Remember: A lot of the quality of your scene will depend on how much care you have put into defining
 //           the relflectance properties of your objects, and the number and type of light sources
 //           in the scene.
}

void rtShade(struct object3D *obj, struct point3D *p, struct point3D *n, struct ray3D *ray, int depth, double a, double b, struct colourRGB *col)
{
 // This function implements the shading model as described in lecture. It takes
 // - A pointer to the first object intersected by the ray (to get the colour properties)
 // - The coordinates of the intersection point (in world coordinates)
 // - The normal at the point
 // - The ray (needed to determine the reflection direction to use for the global component, as well as for
 //   the Phong specular component)
 // - The current racursion depth
 // - The (a,b) texture coordinates (meaningless unless texture is enabled)
 //
 // Returns:
 // - The colour for this ray (using the col pointer)
 //

 struct colourRGB tmp_col;	// Accumulator for colour components
 double R,G,B;			// Colour for the object in R G and B

 // This will hold the colour as we process all the components of
 // the Phong illumination model
 tmp_col.R=0;
 tmp_col.G=0;
 tmp_col.B=0;

 if (obj->texImg==NULL)		// Not textured, use object colour
 {
  R=obj->col.R;
  G=obj->col.G;
  B=obj->col.B;
 }
 else
 {
  // Get object colour from the texture given the texture coordinates (a,b), and the texturing function
  // for the object. Note that we will use textures also for Photon Mapping.
  obj->textureMap(obj->texImg,a,b,&R,&G,&B);
 }

 //////////////////////////////////////////////////////////////
 // TO DO: Implement this function. Refer to the notes for
 // details about the shading model.
 //////////////////////////////////////////////////////////////

 struct point3D light_direction;
 struct ray3D* light;

 struct colourRGB ambient = {0};  // Accumulator for colour components
 struct colourRGB diffuse= {0};  // Accumulator for colour components
 struct colourRGB specular= {0};  // Accumulator for colour components

 struct point3D temp_p, temp_n;
 double temp_a, temp_b, temp_lambda;
 struct object3D * temp_obj;

 struct point3D r;
 struct point3D b2;

            struct colourRGB E_refr;
            E_refr.R = 0;
            E_refr.G = 0;
            E_refr.B = 0;
  struct ray3D *refr_ray;

 pointLS * current = light_list;

 while (current) {
    // build a new light ray pointing from p to the light source
    memcpy(&light_direction, &current->p0, sizeof(struct point3D));
    subVectors(p, &light_direction);
    light = newRay(p, &light_direction);

// printf("%f, %f, %f, %f, %f, %f\n", p->px, p->py, p->pz, light_direction.px, light_direction.py, light_direction.pz);

    findFirstHit(light, &temp_lambda, obj, &temp_obj, &temp_p, &temp_n, &temp_a, &temp_b);

    // ambient light color
    ambient.R += obj->alb.ra * current->col.R;
    ambient.G += obj->alb.ra * current->col.G;
    ambient.B += obj->alb.ra * current->col.B;

    // diffuse light color
    if (temp_lambda < 0 || temp_lambda > 1) {
      // if there's no object between point and light
        normalize(&light_direction);

      double dot_n_s = dot(n, &light_direction);

      diffuse.R += obj->alb.rd * current->col.R * max(dot_n_s, 0);
      diffuse.G += obj->alb.rd * current->col.G * max(dot_n_s, 0);
      diffuse.B += obj->alb.rd * current->col.B * max(dot_n_s, 0);

      // specular light color

      // // find r = -s + 2(dot(n,s))n
      r.px = 2 * dot(&light_direction, n) * n->px;
      r.py = 2 * dot(&light_direction, n) * n->py;
      r.pz = 2 * dot(&light_direction, n) * n->pz;
      r.pw = 1;
      subVectors(&light_direction, &r);
      normalize(&r);

      // // find b:= point to camera
      b2.px = -ray->d.px;
      b2.py = -ray->d.py;
      b2.pz = -ray->d.pz;
      b2.pw = 1;
      normalize(&b2);

      specular.R += obj->alb.rs * current->col.R * pow(max(0, dot(&r, &b2)), obj->shinyness);
      specular.G += obj->alb.rs * current->col.G * pow(max(0, dot(&r, &b2)), obj->shinyness);
      specular.B += obj->alb.rs * current->col.B * pow(max(0, dot(&r, &b2)), obj->shinyness);
    
    } else {
      ambient = {1-obj->alpha, 1-obj->alpha, 1-obj->alpha};
      specular = {1-obj->alpha, 1-obj->alpha, 1-obj->alpha};
      diffuse = {1-obj->alpha, 1-obj->alpha, 1-obj->alpha};
    }

      if (depth < MAX_DEPTH){
        point3D ms;
        colourRGB E_spec;
        // compute mirror direction: ms = - 2 * dot(d, n) * n + d
        double temp_dot_value = dot(&ray->d, n);
        ms.px = - 2 * temp_dot_value * n->px;
        ms.py = - 2 * temp_dot_value * n->py;
        ms.pz = - 2 * temp_dot_value * n->pz;
        ms.pw = 1;
        // construct new mirror direction
        // memcpy(&m, &ray->d, sizeof(struct point3D));
        addVectors(&ray->d, &ms);
        normalize(&ms);

        // If OBJ has specular reflection
        if (obj->alb.rs != 0){
          // create the ray from intersection point p along mirror direction 
          ray3D * ref_ray = newRay(p, &ms);
          rayTrace(ref_ray, depth++, &E_spec, obj);
          // add reflected color E_spec in, scaled by rg
          specular.R += obj->alb.rg * E_spec.R * current->col.R;
          specular.G += obj->alb.rg * E_spec.G * current->col.G;
          specular.B += obj->alb.rg * E_spec.B * current->col.B;

          free(ref_ray);
        }

        if (obj->alpha < 1) {

          double x,y,z;
          double index_ratio;
          double dot_n_d, sqrt_value, temp_value;
          point3D refr_dir;
          point3D relative_n;

          // refr_dir = index_ratio*d + 
          //      {index_ratio*dot(n, d) - 
          //        sqrt[1 - (index_ratio)^2*(1 - dot(n, d)^2)] } * n

          // check if ray entering or exiting the object
          // calculate corresponding index_ratio and dot(n, d)
          dot_n_d = dot(n, &ray->d);
          if ( dot_n_d > 0){
            // n ,d same direction, exiting the object 
            index_ratio =  obj->r_index;
            // set normal to other side of the surface
            relative_n.px = -n->px;
            relative_n.py = -n->py;
            relative_n.pz = -n->pz;
            relative_n.pw = 1;
            // update dot_n_d
            dot_n_d = dot(&relative_n, &ray->d);
          } else{
            // entering the object
            index_ratio = 1/obj->r_index;
            relative_n.px = n->px;
            relative_n.py = n->py;
            relative_n.pz = n->pz;
            relative_n.pw = 1;
          }
          sqrt_value = 1 - pow(index_ratio, 2) * (1 - pow(dot_n_d, 2));
          if (sqrt_value >= 0) {

            temp_value = index_ratio * dot_n_d - sqrt(sqrt_value);
        
            refr_dir.px = index_ratio * ray->d.px + temp_value * relative_n.px;
            refr_dir.py = index_ratio * ray->d.py + temp_value * relative_n.py;
            refr_dir.pz = index_ratio * ray->d.pz + temp_value * relative_n.pz;
            refr_dir.pw = 1;
            
            refr_ray = newRay(p, &refr_dir);
            rayTrace(refr_ray, depth++, &E_refr, obj);
            
            // Update color for refraction
            E_refr.R = E_refr.R * (1 - obj->alpha);
            E_refr.G = E_refr.G * (1 - obj->alpha);
            E_refr.B = E_refr.B * (1 - obj->alpha);

            // Free refraction ray
            free(refr_ray);
          }
        }

      }

    
    current = current->next;
    free(light);
 }

 // Be sure to update 'col' with the final colour computed here!
 col->R = clip(R * (ambient.R + diffuse.R + specular.R) * obj->alpha + E_refr.R);
 col->G = clip(G * (ambient.G + diffuse.G + specular.G) * obj->alpha + E_refr.G);
 col->B = clip(B * (ambient.B + diffuse.B + specular.B) * obj->alpha + E_refr.B);
 // printf("(%f, %f, %f)\n", col->R, col->G, col->B);

// testing the normal gradient
// col->R = (n->px + 1)/2.0;
// col->G = (n->py + 1)/2.0;
// col->B = (n->pz + 1)/2.0;

// free(&light);
// free(&light_direction);
// free(&temp_obj);

 return;

}


void findFirstHit(struct ray3D *ray, double *lambda, struct object3D *Os, struct object3D **obj, struct point3D *p, struct point3D *n, double *a, double *b)
{
 // Find the closest intersection between the ray and any objects in the scene.
 // It returns:
 //   - The lambda at the intersection (or < 0 if no intersection)
 //   - The pointer to the object at the intersection (so we can evaluate the colour in the shading function)
 //   - The location of the intersection point (in p)
 //   - The normal at the intersection point (in n)
 //
 // Os is the 'source' object for the ray we are processing, can be NULL, and is used to ensure we don't 
 // return a self-intersection due to numerical errors for recursive raytrace calls.
 //

 /////////////////////////////////////////////////////////////
 // TO DO: Implement this function. See the notes for
 // reference of what to do in here
 /////////////////////////////////////////////////////////////

  *lambda = -1;
  double intersect_lamdba = -1;
  struct point3D intersect_p, intersect_n;
  double intersect_a, intersect_b = 0;

  object3D* current = object_list;
  while (current) {
    if (current != Os) {
      // make sure it's no intersecting with self
      current->intersect(current, ray, &intersect_lamdba, &intersect_p, &intersect_n, &intersect_a, &intersect_b);
      if (intersect_lamdba > 0) {
        if (*lambda < 0 || intersect_lamdba < *lambda)  {
          *lambda = intersect_lamdba;
          *p = intersect_p;
          *n = intersect_n;
          *a = intersect_a;
          *b = intersect_b;
          *obj = current;
        }
      }
    }
    current = current -> next;
  }

}

void rayTrace(struct ray3D *ray, int depth, struct colourRGB *col, struct object3D *Os)
{
 // Ray-Tracing function. It finds the closest intersection between
 // the ray and any scene objects, calls the shading function to
 // determine the colour at this intersection, and returns the
 // colour.
 //
 // Os is needed for recursive calls to ensure that findFirstHit will
 // not simply return a self-intersection due to numerical
 // errors. For the top level call, Os should be NULL. And thereafter
 // it will correspond to the object from which the recursive
 // ray originates.
 //

 double lambda;		// Lambda at intersection
 double a,b;		// Texture coordinates
 struct object3D *obj;	// Pointer to object at intersection
 struct point3D p;	// Intersection point
 struct point3D n;	// Normal at intersection
 struct colourRGB I;	// Colour returned by shading function

 if (depth>MAX_DEPTH)	// Max recursion depth reached. Return invalid colour.
 {
  col->R=-1;
  col->G=-1;
  col->B=-1;
  return;
 }

  ///////////////////////////////////////////////////////
  // TO DO: Complete this function. Refer to the notes
  // if you are unsure what to do here.
  ///////////////////////////////////////////////////////

  //void findFirstHit(struct ray3D *ray, double *lambda, struct object3D *Os,
  // struct object3D **obj, struct point3D *p, struct point3D *n, double *a, double *b)
  //   - The lambda at the intersection (or < 0 if no intersection)

  findFirstHit(ray, &lambda, Os, &obj, &p, &n, &a, &b);

  if (lambda < 0) {
    // no intersection, set as background color
    col->R = -1;
    col->G = -1;
    col->B = -1;
    return;
  } else {
    // if there's an intersection, call shader to shade it to correct color

    // fprintf(stderr,"."); // "texture coordinates in rayTrace: %f, %f\n", a, b); 
    // col->R = obj->col.R;
    // col->G = obj->col.G;
    // col->B = obj->col.B;


    rtShade(obj, &p, &n, ray, depth, a, b, &I);
    // printf("obj:(%f,%f,%f), normal: (%f, %f, %f)\n", obj->col.R,obj->col.G,obj->col.B, n.px, n.py, n.pz);
    col->R = I.R;
    col->G = I.G;
    col->B = I.B;
    // return;
  }

}

int main(int argc, char *argv[])
{
 // Main function for the raytracer. Parses input parameters,
 // sets up the initial blank image, and calls the functions
 // that set up the scene and do the raytracing.
 struct image *im;	// Will hold the raytraced image
 struct view *cam;	// Camera and view for this scene
 int sx;		// Size of the raytraced image
 int antialiasing;	// Flag to determine whether antialiaing is enabled or disabled
 char output_name[1024];	// Name of the output file for the raytraced .ppm image
 struct point3D e;		// Camera view parameters 'e', 'g', and 'up'
 struct point3D g;
 struct point3D up;
 double du, dv;			// Increase along u and v directions for pixel coordinates
 struct point3D pc,d;		// Point structures to keep the coordinates of a pixel
                        // and the direction or a ray
 struct ray3D *ray;		// Structure to keep the ray from e to a pixel
 struct colourRGB col;		// Return colour for raytraced pixels
 struct colourRGB background;   // Background colour
 int i,j;			// Counters for pixel coordinates
 unsigned char *rgbIm;
 int offset;

 // struct image* backg = readPPMimage("./mytex/blue_sky_background.ppm");
 // unsigned char *backgroundimage=(unsigned char *)backg->rgbdata;

 int antialias_sample;
 int k;
 struct colourRGB aa_color_sum;

 if (argc<5)
 {
  fprintf(stderr,"RayTracer: Can not parse input parameters\n");
  fprintf(stderr,"USAGE: RayTracer size rec_depth antialias output_name\n");
  fprintf(stderr,"   size = Image size (both along x and y)\n");
  fprintf(stderr,"   rec_depth = Recursion depth\n");
  fprintf(stderr,"   antialias = A single digit, 0 disables antialiasing. Anything else enables antialiasing\n");
  fprintf(stderr,"   output_name = Name of the output file, e.g. MyRender.ppm\n");
  exit(0);
 }
 sx=atoi(argv[1]);
 MAX_DEPTH=atoi(argv[2]);
 if (atoi(argv[3])==0) antialiasing=0; else antialiasing=1;
 strcpy(&output_name[0],argv[4]);

 fprintf(stderr,"Rendering image at %d x %d\n",sx,sx);
 fprintf(stderr,"Recursion depth = %d\n",MAX_DEPTH);
 if (!antialiasing) {
  antialias_sample = 1;
  fprintf(stderr,"Antialising is off\n");
 }
 else {
  antialias_sample = 4;
  fprintf(stderr,"Antialising is on\n");
 }

 fprintf(stderr,"Output file name: %s\n",output_name);

 object_list=NULL;
 light_list=NULL;

 // Allocate memory for the new image
 im=newImage(sx, sx);
 if (!im)
 {
  fprintf(stderr,"Unable to allocate memory for raytraced image\n");
  exit(0);
 }
 else rgbIm=(unsigned char *)im->rgbdata;

 ///////////////////////////////////////////////////
 // TO DO: You will need to implement several of the
 //        functions below. For Assignment 3, you can use
 //        the simple scene already provided. But
 //        for Assignment 4 you need to create your own
 //        *interesting* scene.
 ///////////////////////////////////////////////////
 buildScene();		// Create a scene. This defines all the
			// objects in the world of the raytracer

 //////////////////////////////////////////
 // TO DO: For Assignment 3 you can use the setup
 //        already provided here. For Assignment 4
 //        you may want to move the camera
 //        and change the view parameters
 //        to suit your scene.
 //////////////////////////////////////////

 // Mind the homogeneous coordinate w of all vectors below. DO NOT
 // forget to set it to 1, or you'll get junk out of the
 // geometric transformations later on.

 // Camera center is at (0,0,-1)
 e.px=0;
 e.py=0;
 e.pz=-3;
 e.pw=1;

 // To define the gaze vector, we choose a point 'pc' in the scene that
 // the camera is looking at, and do the vector subtraction pc-e.
 // Here we set up the camera to be looking at the origin, so g=(0,0,0)-(0,0,-1)
 g.px=0;
 g.py=0;
 g.pz=3; // -_- consistent with up
 g.pw=1;

 // Define the 'up' vector to be the Y axis
 up.px=0;
 up.py=1;
 up.pz=0;
 up.pw=1;

 // Set up view with given the above vectors, a 4x4 window,
 // and a focal length of -1 (why? where is the image plane?)
 // Note that the top-left corner of the window is at (-2, 2)
 // in camera coordinates.
 cam=setupView(&e, &g, &up, -3, -2, 2, 4);

 if (cam==NULL)
 {
  fprintf(stderr,"Unable to set up the view and camera parameters. Our of memory!\n");
  cleanup(object_list,light_list);
  deleteImage(im);
  exit(0);
 }




 // Do the raytracing
 //////////////////////////////////////////////////////
 // TO DO: You will need code here to do the raytracing
 //        for each pixel in the image. Refer to the
 //        lecture notes, in particular, to the
 //        raytracing pseudocode, for details on what
 //        to do here. Make sure you undersand the
 //        overall procedure of raytracing for a single
 //        pixel.
 //////////////////////////////////////////////////////
 du=cam->wsize/(sx-1);		// du and dv. In the notes in terms of wl and wr, wt and wb,
 dv=-cam->wsize/(sx-1);		// here we use wl, wt, and wsize. du=dv since the image is
				// and dv is negative since y increases downward in pixel
				// coordinates and upward in camera coordinates.

 fprintf(stderr,"View parameters:\n");
 fprintf(stderr,"Left=%f, Top=%f, Width=%f, f=%f\n",cam->wl,cam->wt,cam->wsize,cam->f);
 fprintf(stderr,"Camera to world conversion matrix (make sure it makes sense!):\n");
 printmatrix(cam->C2W);
 fprintf(stderr,"World to camera conversion matrix\n");
 printmatrix(cam->W2C);
 fprintf(stderr,"\n");

// fprintf(stderr,"num of samples: %d\n",antialias_sample);

 fprintf(stderr,"Rendering row: ");

 /**
 * Reference: https://computing.llnl.gov/tutorials/openMP/
 * http://www.geeksforgeeks.org/multithreading-c-2/
 **/
 #pragma omp parallel for schedule(dynamic,32) shared(antialias_sample, rgbIm, object_list, light_list) private(j)
 for (j=0;j<sx;j++)		// For each of the pixels in the image
 {
  fprintf(stderr,"%d/%d, ",j,sx);
  // if(j==100){
  //   getchar();
  // }

  #pragma omp parallel for private(k, pc, d, ray, col, aa_color_sum, offset, i)
  for (i=0;i<sx;i++)
  {

    offset = (i+j*sx) * 3; // 3 for r g and b

     // Set up background colour here
     background.R=-1; // backgroundimage[offset];
     background.G=-1; // backgroundimage[offset+1];
     background.B=-1; // backgroundimage[offset+2];


    ///////////////////////////////////////////////////////////////////
    // TO DO - complete the code that should be in this loop to do the
    //         raytracing!
    ///////////////////////////////////////////////////////////////////

    aa_color_sum.R = 0;
    aa_color_sum.G = 0;
    aa_color_sum.B = 0;

    // #pragma omp parallel for private (k, pc, d, ray, col)
    for (k=0; k< antialias_sample; k++) {
      // the pixel on view plane:
      pc.px = cam->wl + (i + antialiasing * (k % 2))*du;
      pc.py = cam->wt + (j + antialiasing * (k / 2))*dv;
      pc.pz = cam->f;
      pc.pw = 1;
      // convert to the world coordinates
      matVecMult(cam->C2W, &pc);

      // the direction vector point from camera to the point on view plane
      d.px = pc.px - cam->e.px;
      d.py = pc.py - cam->e.py;
      d.pz = pc.pz - cam->e.pz;
      d.pw = 0;
      normalize(&d);

      pc.px += d.px * 0.01;
      pc.py += d.py * 0.01;
      pc.pz += d.pz * 0.01;

      // shoot the ray
      ray = newRay(&pc, &d);

      // Shoot the ray and find out color of that pixel
      rayTrace(ray, 0, &col, NULL); // first recursive call

      if (col.R == -1 || col.G == -1 || col.B == -1) {
        col.R = background.R;
        col.G = background.G;
        col.B = background.B;
      }

      aa_color_sum.R += col.R;
      aa_color_sum.G += col.G;
      aa_color_sum.B += col.B;

      free(ray);
    }

    *(rgbIm + offset + 0) = clip(aa_color_sum.R / antialias_sample) * 255;
    *(rgbIm + offset + 1) = clip(aa_color_sum.G / antialias_sample) * 255;
    *(rgbIm + offset + 2) = clip(aa_color_sum.B / antialias_sample) * 255;

    // free(ray);

    // printf("(%f,%f,%f),", *(rgbIm + offset + 0), *(rgbIm + offset + 1), *(rgbIm + offset + 2));

  } // end for i
  // printf("\n");

 } // end for j


 fprintf(stderr,"\nDone!\n");

 // Output rendered image
 imageOutput(im,output_name);

 // Exit section. Clean up and return.
 cleanup(object_list,light_list);		// Object and light lists
 deleteImage(im);				// Rendered image
 // deleteImage(backg);
 free(cam);					// camera view
 exit(0);
}
