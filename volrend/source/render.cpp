#include "incl.h"

float obslight[NM];	
float obshighlight[NM];

void Render() {
    Observer_Transform_Light_Vector();
    Compute_Observer_Transformed_Highlight_Vector();
    Ray_Trace();
}

void Observer_Transform_Light_Vector() {
  float inv_magnitude;
  Transform_Point(light[X],light[Y],light[Z],
		  &obslight[X],&obslight[Y],&obslight[Z]);

  inv_magnitude = 1.0/sqrt(obslight[X]*obslight[X] +
		   obslight[Y]*obslight[Y] +
		   obslight[Z]*obslight[Z]);
  obslight[X] = obslight[X] * inv_magnitude;
  obslight[Y] = obslight[Y] * inv_magnitude;
  obslight[Z] = obslight[Z] * inv_magnitude;
}


void Compute_Observer_Transformed_Highlight_Vector() {
  float inv_magnitude;
  float obseye[NM];
  float brightness=1.0;
  float eye[NM];

  eye[X] = 0.0;
  eye[Y] = 0.0;
  eye[Z] = -1.0;
  Transform_Point(eye[X],eye[Y],eye[Z],&obseye[X],&obseye[Y],&obseye[Z]);

  inv_magnitude = 1.0/sqrt(obseye[X]*obseye[X] +
		   obseye[Y]*obseye[Y] +
		   obseye[Z]*obseye[Z]);
  obseye[X] = obseye[X] * inv_magnitude;
  obseye[Y] = obseye[Y] * inv_magnitude;
  obseye[Z] = obseye[Z] * inv_magnitude;

  obshighlight[X] = obslight[X] + obseye[X];
  obshighlight[Y] = obslight[Y] + obseye[Y];
  obshighlight[Z] = obslight[Z] + obseye[Z];

  inv_magnitude = 1.0/sqrt(obshighlight[X]*obshighlight[X] +
		   obshighlight[Y]*obshighlight[Y] +
		   obshighlight[Z]*obshighlight[Z]);
  obshighlight[X] = obshighlight[X] * inv_magnitude * brightness;
  obshighlight[Y] = obshighlight[Y] * inv_magnitude * brightness;
  obshighlight[Z] = obshighlight[Z] * inv_magnitude * brightness;
}
