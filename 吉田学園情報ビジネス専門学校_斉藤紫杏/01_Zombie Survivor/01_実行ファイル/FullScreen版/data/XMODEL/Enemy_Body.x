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
 86;
 3.46092;-0.23897;-2.76515;,
 4.32615;-1.45354;-2.76515;,
 3.46092;-1.45354;-3.45644;,
 -3.46092;-1.45354;-3.45644;,
 -4.32615;-1.45354;-2.76515;,
 -3.46092;-0.23897;-2.76515;,
 3.46092;-11.17012;-3.45644;,
 4.32615;-11.17012;-2.76515;,
 3.46092;-12.38469;-2.76515;,
 3.46092;-1.45354;3.45644;,
 4.32615;-1.45354;2.76515;,
 3.46092;-0.23897;2.76515;,
 -3.46092;-12.38469;-2.76515;,
 -4.32615;-11.17012;-2.76515;,
 -3.46092;-11.17012;-3.45644;,
 3.46092;-12.38469;2.76515;,
 4.32615;-11.17012;2.76515;,
 3.46092;-11.17012;3.45644;,
 -3.46092;-0.23897;2.76515;,
 -4.32615;-1.45354;2.76515;,
 -3.46092;-1.45354;3.45644;,
 -3.46092;-11.17012;3.45644;,
 -4.32615;-11.17012;2.76515;,
 -3.46092;-12.38469;2.76515;,
 2.87771;-5.83386;-2.87398;,
 3.59714;-5.83386;-2.29919;,
 2.87771;-5.83386;2.87398;,
 3.59714;-5.83386;2.29919;,
 -2.87771;-5.83386;-2.87398;,
 -3.59714;-5.83386;-2.29919;,
 -2.87771;-5.83386;2.87398;,
 -3.59714;-5.83386;2.29919;,
 4.28876;-0.23897;0.03276;,
 5.36096;-1.45354;0.03276;,
 4.28876;-12.38469;0.03276;,
 5.36096;-11.17012;0.03276;,
 -4.28876;-0.23897;0.03276;,
 -5.36096;-1.45354;0.03276;,
 -4.28876;-12.38469;0.03276;,
 -5.36096;-11.17012;0.03276;,
 4.45757;-5.83386;0.03276;,
 -4.45757;-5.83386;0.03276;,
 -0.05143;-0.23897;-3.40952;,
 3.46092;-0.23897;-2.76515;,
 3.46092;-1.45354;-3.45644;,
 -0.05143;-1.45354;-4.26190;,
 -0.05143;-11.17012;-4.26190;,
 3.46092;-11.17012;-3.45644;,
 3.46092;-12.38469;-2.76515;,
 -0.05143;-12.38469;-3.40952;,
 -0.05143;-1.45354;4.26190;,
 -0.05143;-0.23897;3.40952;,
 -0.05143;-12.38469;3.40952;,
 -0.05143;-11.17012;4.26190;,
 -0.05143;-5.83386;-3.54371;,
 2.87771;-5.83386;-2.87398;,
 -0.05143;-5.83386;3.54371;,
 -0.05143;-0.23897;0.03276;,
 4.28876;-0.23897;0.03276;,
 -0.05143;-12.38469;0.03276;,
 0.00000;-1.56323;-5.11785;,
 -0.00000;-11.36452;-4.25395;,
 -1.19179;-1.56323;-4.86482;,
 -0.00000;-11.36452;-4.25395;,
 -1.68545;-1.56323;-4.25395;,
 -0.00000;-11.36452;-4.25395;,
 -1.19179;-1.56323;-3.64308;,
 -0.00000;-11.36452;-4.25395;,
 0.00000;-1.56323;-3.39005;,
 -0.00000;-11.36452;-4.25395;,
 1.19179;-1.56323;-3.64308;,
 -0.00000;-11.36452;-4.25395;,
 1.68545;-1.56323;-4.25395;,
 -0.00000;-11.36452;-4.25395;,
 1.19179;-1.56323;-4.86482;,
 -0.00000;-11.36452;-4.25395;,
 0.00000;-1.56323;-5.11785;,
 0.00000;-1.56323;-4.25395;,
 0.00000;-1.56323;-5.11785;,
 -1.19179;-1.56323;-4.86482;,
 -1.68545;-1.56323;-4.25395;,
 -1.19179;-1.56323;-3.64308;,
 0.00000;-1.56323;-3.39005;,
 1.19179;-1.56323;-3.64308;,
 1.68545;-1.56323;-4.25395;,
 1.19179;-1.56323;-4.86482;;
 
 72;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;12,13,14;,
 3;15,16,17;,
 3;18,19,20;,
 3;21,22,23;,
 4;24,2,1,25;,
 4;24,25,7,6;,
 4;26,17,16,27;,
 4;26,27,10,9;,
 4;28,14,13,29;,
 4;28,29,4,3;,
 4;30,20,19,31;,
 4;30,31,22,21;,
 4;32,11,10,33;,
 4;32,33,1,0;,
 4;34,8,7,35;,
 4;34,35,16,15;,
 4;36,5,4,37;,
 4;36,37,19,18;,
 4;38,23,22,39;,
 4;38,39,13,12;,
 4;35,7,25,40;,
 4;35,40,27,16;,
 4;40,25,1,33;,
 4;40,33,10,27;,
 4;37,4,29,41;,
 4;37,41,31,19;,
 4;41,29,13,39;,
 4;41,39,22,31;,
 4;42,43,44,45;,
 4;42,45,3,5;,
 4;46,47,48,49;,
 4;46,49,12,14;,
 4;50,9,11,51;,
 4;50,51,18,20;,
 4;52,15,17,53;,
 4;52,53,21,23;,
 4;46,14,28,54;,
 4;46,54,55,47;,
 4;54,28,3,45;,
 4;54,45,44,55;,
 4;50,20,30,56;,
 4;50,56,26,9;,
 4;56,30,21,53;,
 4;56,53,17,26;,
 4;42,5,36,57;,
 4;42,57,58,43;,
 4;57,36,18,51;,
 4;57,51,11,32;,
 4;52,23,38,59;,
 4;52,59,34,15;,
 4;59,38,12,49;,
 4;59,49,48,34;,
 3;60,61,62;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;68,69,70;,
 3;70,71,72;,
 3;72,73,74;,
 3;74,75,76;,
 3;77,78,79;,
 3;77,79,80;,
 3;77,80,81;,
 3;77,81,82;,
 3;77,82,83;,
 3;77,83,84;,
 3;77,84,85;,
 3;77,85,78;;
 
 MeshMaterialList {
  12;
  72;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
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
  67;
  -0.435336;0.733628;0.521797;,
  0.434068;0.734072;0.522229;,
  -0.435890;0.734269;-0.520432;,
  0.434622;0.734714;-0.520864;,
  -0.430598;0.160417;-0.888173;,
  0.427692;0.160731;-0.889520;,
  -0.429539;-0.175730;-0.885785;,
  0.426641;-0.176036;-0.887124;,
  -0.435890;-0.734269;-0.520432;,
  0.434622;-0.734714;-0.520864;,
  -0.435336;-0.733628;0.521797;,
  0.434068;-0.734072;0.522229;,
  -0.429539;-0.175730;0.885785;,
  0.426641;-0.176036;0.887124;,
  -0.430598;0.160417;0.888173;,
  0.427692;0.160731;0.889520;,
  0.795102;0.176251;0.580301;,
  0.792555;-0.193134;0.578408;,
  0.797218;0.176691;-0.577255;,
  0.794655;-0.193605;-0.575361;,
  -0.792555;-0.193134;0.578408;,
  -0.795102;0.176251;0.580301;,
  -0.794655;-0.193605;-0.575361;,
  -0.797218;0.176691;-0.577255;,
  -0.437420;-0.015519;-0.899123;,
  0.434159;-0.015513;-0.900703;,
  -0.437420;-0.015519;0.899123;,
  0.434159;-0.015513;0.900703;,
  0.808092;-0.017122;0.588807;,
  0.810604;-0.017157;-0.585343;,
  -0.808092;-0.017122;0.588807;,
  -0.810604;-0.017157;-0.585343;,
  -0.427673;0.903932;0.001588;,
  0.427673;0.903932;0.001588;,
  -0.427673;-0.903932;0.001588;,
  0.427673;-0.903932;0.001588;,
  0.971165;0.238376;0.003912;,
  0.966797;-0.255516;0.003894;,
  -0.966797;-0.255516;0.003894;,
  -0.971165;0.238376;0.003912;,
  0.999830;-0.017904;0.004286;,
  -0.999830;-0.017904;0.004286;,
  -0.001439;0.878109;0.478459;,
  -0.001439;0.878109;-0.478459;,
  -0.003262;0.201623;-0.979458;,
  -0.003254;-0.215617;-0.976473;,
  -0.001439;-0.878109;-0.478459;,
  -0.001439;-0.878109;0.478459;,
  -0.003254;-0.215617;0.976473;,
  -0.003262;0.201623;0.979458;,
  -0.003611;-0.014370;-0.999890;,
  -0.003611;-0.014370;0.999890;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.087801;-0.996138;,
  -0.518531;-0.115851;-0.847174;,
  -0.770913;-0.132568;-0.622992;,
  -0.518531;-0.115851;0.847174;,
  0.000000;-0.087801;0.996138;,
  0.518531;-0.115852;0.847174;,
  0.770913;-0.132568;0.622991;,
  0.518531;-0.115852;-0.847174;,
  -0.285271;-0.112630;-0.951806;,
  0.000000;1.000000;0.000000;,
  -0.770913;-0.132568;0.622992;,
  -0.285271;-0.112630;0.951806;,
  0.770913;-0.132568;-0.622991;;
  72;
  3;3,18,5;,
  3;4,23,2;,
  3;7,19,9;,
  3;15,16,1;,
  3;8,22,6;,
  3;11,17,13;,
  3;0,21,14;,
  3;12,20,10;,
  4;25,5,18,29;,
  4;25,29,19,7;,
  4;27,13,17,28;,
  4;27,28,16,15;,
  4;24,6,22,31;,
  4;24,31,23,4;,
  4;26,14,21,30;,
  4;26,30,20,12;,
  4;33,1,16,36;,
  4;33,36,18,3;,
  4;35,9,19,37;,
  4;35,37,17,11;,
  4;32,2,23,39;,
  4;32,39,21,0;,
  4;34,10,20,38;,
  4;34,38,22,8;,
  4;37,19,29,40;,
  4;37,40,28,17;,
  4;40,29,18,36;,
  4;40,36,16,28;,
  4;39,23,31,41;,
  4;39,41,30,21;,
  4;41,31,22,38;,
  4;41,38,20,30;,
  4;43,3,5,44;,
  4;43,44,4,2;,
  4;45,7,9,46;,
  4;45,46,8,6;,
  4;49,15,1,42;,
  4;49,42,0,14;,
  4;47,11,13,48;,
  4;47,48,12,10;,
  4;45,6,24,50;,
  4;45,50,25,7;,
  4;50,24,4,44;,
  4;50,44,5,25;,
  4;49,14,26,51;,
  4;49,51,27,15;,
  4;51,26,12,48;,
  4;51,48,13,27;,
  4;43,2,32,52;,
  4;43,52,33,3;,
  4;52,32,0,42;,
  4;52,42,1,33;,
  4;47,10,34,53;,
  4;47,53,35,11;,
  4;53,34,8,46;,
  4;53,46,9,35;,
  3;54,62,55;,
  3;55,62,56;,
  3;64,65,57;,
  3;57,65,58;,
  3;58,65,59;,
  3;59,60,60;,
  3;66,66,61;,
  3;61,62,54;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;;
 }
 MeshTextureCoords {
  86;
  0.142712;0.511949;,
  0.159485;0.572677;,
  0.125103;0.572677;,
  0.874897;0.572677;,
  0.840515;0.572677;,
  0.857288;0.511949;,
  0.125103;1.058506;,
  0.159485;1.058506;,
  0.142712;1.119235;,
  0.374897;0.572677;,
  0.340515;0.572677;,
  0.357288;0.511949;,
  0.857288;1.119235;,
  0.840515;1.058506;,
  0.874897;1.058506;,
  0.357288;1.119235;,
  0.340515;1.058506;,
  0.374897;1.058506;,
  0.642712;0.511949;,
  0.659485;0.572677;,
  0.625103;0.572677;,
  0.625103;1.058506;,
  0.659485;1.058506;,
  0.642712;1.119235;,
  0.125103;0.791693;,
  0.159485;0.791693;,
  0.374897;0.791693;,
  0.340515;0.791693;,
  0.874897;0.791693;,
  0.840515;0.791693;,
  0.625103;0.791693;,
  0.659485;0.791693;,
  0.251216;0.511949;,
  0.250973;0.572677;,
  0.251216;1.119235;,
  0.250973;1.058506;,
  0.748784;0.511949;,
  0.749027;0.572677;,
  0.748784;1.119235;,
  0.749027;1.058506;,
  0.251170;0.791693;,
  0.748830;0.791693;,
  0.997599;0.511949;,
  1.142712;0.511949;,
  1.125103;0.572677;,
  0.998080;0.572677;,
  0.998080;1.058506;,
  1.125103;1.058506;,
  1.142712;1.119235;,
  0.997599;1.119235;,
  0.501920;0.572677;,
  0.502401;0.511949;,
  0.502401;1.119235;,
  0.501920;1.058506;,
  0.997690;0.791693;,
  1.125103;0.791693;,
  0.502310;0.791693;,
  0.659732;0.511949;,
  1.251216;0.511949;,
  0.659732;1.119235;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
