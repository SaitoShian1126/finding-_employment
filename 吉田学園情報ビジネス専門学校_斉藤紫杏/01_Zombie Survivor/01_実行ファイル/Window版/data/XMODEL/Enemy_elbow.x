xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 66;
 -0.01472;2.15559;0.00000;,
 0.41059;1.98679;-0.45381;,
 -0.01472;1.98679;-0.64178;,
 0.58677;1.98679;0.00000;,
 0.41059;1.98679;0.45381;,
 -0.01472;1.98679;0.64178;,
 -0.44005;1.98679;0.45381;,
 -0.61622;1.98679;0.00000;,
 -0.44005;1.98679;-0.45381;,
 0.77116;1.50612;-0.83853;,
 -0.01472;1.50612;-1.18586;,
 0.41059;1.98679;-0.45381;,
 1.09669;1.50612;0.00000;,
 0.77116;1.50612;-0.83853;,
 0.77116;1.50612;0.83853;,
 -0.01472;1.50612;1.18586;,
 -0.80061;1.50612;0.83853;,
 -1.12614;1.50612;0.00000;,
 -0.80061;1.50612;-0.83853;,
 1.01209;0.78672;-1.09560;,
 -0.01472;0.78672;-1.54940;,
 1.43741;0.78672;0.00000;,
 1.01209;0.78672;-1.09560;,
 1.01209;0.78672;1.09560;,
 -0.01472;0.78672;1.54940;,
 -1.04154;0.78672;1.09559;,
 -1.46686;0.78672;0.00000;,
 -1.04154;0.78672;-1.09560;,
 1.09669;-0.06185;-1.18586;,
 -0.01472;-0.06185;-1.67706;,
 1.55705;-0.06185;-0.00000;,
 1.09669;-0.06185;-1.18586;,
 1.09669;-0.06185;1.18586;,
 -0.01472;-0.06185;1.67706;,
 -1.12614;-0.06185;1.18586;,
 -1.58650;-0.06185;0.00000;,
 -1.12614;-0.06185;-1.18586;,
 1.01209;-0.91042;-1.09560;,
 -0.01472;-0.91042;-1.54940;,
 1.43741;-0.91042;-0.00000;,
 1.01209;-0.91042;-1.09560;,
 1.01209;-0.91042;1.09560;,
 -0.01472;-0.91042;1.54940;,
 -1.04154;-0.91042;1.09559;,
 -1.46686;-0.91042;0.00000;,
 -1.04154;-0.91042;-1.09560;,
 0.77116;-1.62980;-0.83853;,
 -0.01472;-1.62980;-1.18586;,
 1.09669;-1.62980;-0.00000;,
 0.77116;-1.62980;-0.83853;,
 0.77116;-1.62980;0.83853;,
 -0.01472;-1.62980;1.18586;,
 -0.80061;-1.62980;0.83853;,
 -1.12614;-1.62980;0.00000;,
 -0.80061;-1.62980;-0.83853;,
 0.41059;-2.11047;-0.45381;,
 -0.01472;-2.11047;-0.64178;,
 0.58677;-2.11047;-0.00000;,
 0.41059;-2.11047;-0.45381;,
 0.41059;-2.11047;0.45381;,
 -0.01472;-2.11047;0.64178;,
 -0.44005;-2.11047;0.45381;,
 -0.61622;-2.11047;0.00000;,
 -0.44005;-2.11047;-0.45381;,
 -0.01472;-2.27929;0.00000;,
 -0.01472;-2.27929;0.00000;;
 
 64;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;11,3,12,13;,
 4;3,4,14,12;,
 4;4,5,15,14;,
 4;5,6,16,15;,
 4;6,7,17,16;,
 4;7,8,18,17;,
 4;8,2,10,18;,
 4;10,9,19,20;,
 4;13,12,21,22;,
 4;12,14,23,21;,
 4;14,15,24,23;,
 4;15,16,25,24;,
 4;16,17,26,25;,
 4;17,18,27,26;,
 4;18,10,20,27;,
 4;20,19,28,29;,
 4;22,21,30,31;,
 4;21,23,32,30;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;26,27,36,35;,
 4;27,20,29,36;,
 4;29,28,37,38;,
 4;31,30,39,40;,
 4;30,32,41,39;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;35,36,45,44;,
 4;36,29,38,45;,
 4;38,37,46,47;,
 4;40,39,48,49;,
 4;39,41,50,48;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;44,45,54,53;,
 4;45,38,47,54;,
 4;47,46,55,56;,
 4;49,48,57,58;,
 4;48,50,59,57;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;54,47,56,63;,
 3;56,55,64;,
 3;58,57,65;,
 3;57,59,64;,
 3;59,60,64;,
 3;60,61,64;,
 3;61,62,64;,
 3;62,63,64;,
 3;63,56,64;;
 
 MeshMaterialList {
  12;
  64;
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Documents\\Visual Studio 2015\\Projects\\3D�l����\\data\\TEXTURE\\���ʕ�.jpeg";
   }
  }
  Material {
   0.179200;0.156800;0.091200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.746400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.778400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.012800;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.787200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.373600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.496000;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.251200;0.392000;0.232000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.339200;0.339200;0.339200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.690400;0.467200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  58;
  0.000002;1.000000;0.000000;,
  0.000003;0.884085;-0.467327;,
  0.347993;0.878067;-0.328480;,
  0.489223;0.872159;0.000000;,
  0.347993;0.878067;0.328480;,
  0.000003;0.884085;0.467327;,
  -0.347990;0.878069;0.328478;,
  -0.489224;0.872159;0.000000;,
  -0.347990;0.878069;-0.328478;,
  0.000003;0.613553;-0.789654;,
  0.579361;0.601454;-0.550085;,
  0.807518;0.589842;0.000000;,
  0.579361;0.601454;0.550085;,
  0.000002;0.613552;0.789654;,
  -0.579361;0.601453;0.550086;,
  -0.807520;0.589840;0.000000;,
  -0.579360;0.601454;-0.550086;,
  0.000002;0.304894;-0.952386;,
  0.691256;0.296146;-0.659138;,
  0.957664;0.287890;0.000000;,
  0.691256;0.296146;0.659138;,
  -0.000000;0.304894;0.952386;,
  -0.691255;0.296146;0.659139;,
  -0.957663;0.287890;0.000001;,
  -0.691254;0.296146;-0.659140;,
  0.000002;0.000000;-1.000000;,
  0.723245;0.000000;-0.690592;,
  1.000000;0.000000;0.000000;,
  0.723245;0.000000;0.690592;,
  -0.000000;0.000000;1.000000;,
  -0.723244;0.000000;0.690592;,
  -1.000000;0.000000;0.000001;,
  -0.723243;0.000000;-0.690593;,
  0.000002;-0.304899;-0.952385;,
  0.691255;-0.296151;-0.659137;,
  0.957662;-0.287895;-0.000000;,
  0.691255;-0.296151;0.659137;,
  -0.000000;-0.304899;0.952385;,
  -0.691254;-0.296151;0.659138;,
  -0.957662;-0.287895;0.000001;,
  -0.691253;-0.296151;-0.659139;,
  0.000003;-0.613557;-0.789651;,
  0.579359;-0.601458;-0.550083;,
  0.807516;-0.589846;-0.000000;,
  0.579359;-0.601458;0.550083;,
  0.000002;-0.613556;0.789651;,
  -0.579359;-0.601457;0.550084;,
  -0.807518;-0.589843;0.000000;,
  -0.579358;-0.601458;-0.550084;,
  0.000003;-0.884078;-0.467340;,
  0.348003;-0.878060;-0.328489;,
  0.489237;-0.872151;-0.000000;,
  0.348003;-0.878060;0.328489;,
  0.000003;-0.884078;0.467340;,
  -0.348001;-0.878061;0.328488;,
  -0.489238;-0.872150;0.000000;,
  -0.348001;-0.878061;-0.328488;,
  0.000002;-1.000000;-0.000000;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;;
 }
 MeshTextureCoords {
  66;
  0.750000;0.392220;,
  1.117049;0.400661;,
  0.996350;0.400661;,
  0.250000;0.400661;,
  0.382951;0.400661;,
  0.503650;0.400661;,
  0.622550;0.400661;,
  0.750000;0.400661;,
  0.877450;0.400661;,
  1.118343;0.424694;,
  0.998025;0.424694;,
  0.117049;0.400661;,
  0.250000;0.424694;,
  0.118343;0.424694;,
  0.381657;0.424694;,
  0.501976;0.424694;,
  0.621319;0.424694;,
  0.750000;0.424694;,
  0.878681;0.424694;,
  1.118697;0.460664;,
  0.998488;0.460664;,
  0.250000;0.460664;,
  0.118697;0.460664;,
  0.381303;0.460664;,
  0.501512;0.460664;,
  0.620976;0.460664;,
  0.750000;0.460664;,
  0.879025;0.460664;,
  1.118786;0.503093;,
  0.998603;0.503093;,
  0.250000;0.503093;,
  0.118786;0.503093;,
  0.381214;0.503093;,
  0.501397;0.503093;,
  0.620890;0.503093;,
  0.750000;0.503093;,
  0.879110;0.503093;,
  1.118697;0.545521;,
  0.998488;0.545521;,
  0.250000;0.545521;,
  0.118697;0.545521;,
  0.381303;0.545521;,
  0.501512;0.545521;,
  0.620976;0.545521;,
  0.750000;0.545521;,
  0.879025;0.545521;,
  1.118343;0.581490;,
  0.998025;0.581490;,
  0.250000;0.581490;,
  0.118343;0.581490;,
  0.381657;0.581490;,
  0.501976;0.581490;,
  0.621319;0.581490;,
  0.750000;0.581490;,
  0.878681;0.581490;,
  1.117049;0.605523;,
  0.996350;0.605523;,
  0.250000;0.605523;,
  0.117049;0.605523;,
  0.382951;0.605523;,
  0.503650;0.605523;,
  0.622550;0.605523;,
  0.750000;0.605523;,
  0.877450;0.605523;,
  0.750000;0.613964;,
  -0.250000;0.613964;;
 }
}
