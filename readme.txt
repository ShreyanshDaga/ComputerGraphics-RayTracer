CSCI 420 Assignment 3 Submission
Name: Shreyansh Daga
USC ID: 6375 3348 33
EMail: sdaga@usc.edu


Feature:                                 Status: finish? (yes/no)

-------------------------------------    -------------------------

1) Ray tracing triangles                  Yes


2) Ray tracing sphere                     Yes

3) Triangle Phong Shading                 Yes

4) Sphere Phong Shading                   Yes

5) Shadows rays                           Yes

6) Still images                           Yes   

7) Extra Credit (up to 20 points)
         Yes

   I have done the following extra credits

1) Soft Shadow
-> Here I have taken for each light source, 9 number of light points around that light source, calculated the color/shadow
   and then averaged it to kind of look like soft transition in shadows

2) Motion Blur
-> Here I have taken one scene file, and in that scene file i have moved one of the spheres in y direction and taken 20 screenshots
and then averaged each screen shot to get a blur image.

3) Animation
-> Here I have 3 spheres bouncing with various frequencies and two light sources moving in x and z direction respectively

4) Recursive Reflection
-> I could not completely implement this. As I was not getting correct reflection at the triangle face, hence light from my triangles
was not containing the additional relfeected light from other objects.


I have the names of folders for each extra credit.
The mandatory is the Basic Ray tracer.
Each folder also has its own scene file within itself.

I have also provided the scene files in the root directory of the VS project.

I could not get a release version as picLibrary.lib was throqing error and after many attempts i gave up. THe debug mode runs fine.

THe frames for animation are nummberes 000.jpeg to 149.jpg, and they are in the seperate folder.