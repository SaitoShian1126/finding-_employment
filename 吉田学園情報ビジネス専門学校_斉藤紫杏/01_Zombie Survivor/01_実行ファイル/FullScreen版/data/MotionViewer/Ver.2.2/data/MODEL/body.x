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
 96;
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
 5.36096;-11.17012;0.03276;,
 4.32615;-11.17012;-2.76515;,
 3.59714;-5.83386;-2.29919;,
 4.45757;-5.83386;0.03276;,
 3.59714;-5.83386;2.29919;,
 4.32615;-11.17012;2.76515;,
 4.32615;-1.45354;-2.76515;,
 5.36096;-1.45354;0.03276;,
 -5.36096;-1.45354;0.03276;,
 -4.32615;-1.45354;-2.76515;,
 -3.59714;-5.83386;-2.29919;,
 -4.45757;-5.83386;0.03276;,
 -3.59714;-5.83386;2.29919;,
 -4.32615;-1.45354;2.76515;,
 -4.32615;-11.17012;-2.76515;,
 -5.36096;-11.17012;0.03276;,
 -0.05143;-0.23897;-3.40952;,
 -0.05143;-1.45354;-4.26190;,
 -0.05143;-11.17012;-4.26190;,
 -0.05143;-12.38469;-3.40952;,
 -0.05143;-1.45354;4.26190;,
 -0.05143;-0.23897;3.40952;,
 -0.05143;-12.38469;3.40952;,
 -0.05143;-11.17012;4.26190;,
 -0.05143;-11.17012;-4.26190;,
 -3.46092;-11.17012;-3.45644;,
 -2.87771;-5.83386;-2.87398;,
 -0.05143;-5.83386;-3.54371;,
 2.87771;-5.83386;-2.87398;,
 3.46092;-11.17012;-3.45644;,
 -0.05143;-1.45354;-4.26190;,
 3.46092;-1.45354;-3.45644;,
 -0.05143;-1.45354;4.26190;,
 -3.46092;-1.45354;3.45644;,
 -2.87771;-5.83386;2.87398;,
 -0.05143;-5.83386;3.54371;,
 2.87771;-5.83386;2.87398;,
 3.46092;-1.45354;3.45644;,
 -0.05143;-11.17012;4.26190;,
 3.46092;-11.17012;3.45644;,
 -0.05143;-0.23897;-3.40952;,
 -3.46092;-0.23897;-2.76515;,
 -4.28876;-0.23897;0.03276;,
 -0.05143;-0.23897;0.03276;,
 4.28876;-0.23897;0.03276;,
 3.46092;-0.23897;-2.76515;,
 -0.05143;-0.23897;3.40952;,
 3.46092;-0.23897;2.76515;,
 -0.05143;-12.38469;3.40952;,
 -3.46092;-12.38469;2.76515;,
 -4.28876;-12.38469;0.03276;,
 -0.05143;-12.38469;0.03276;,
 4.28876;-12.38469;0.03276;,
 3.46092;-12.38469;2.76515;,
 -0.05143;-12.38469;-3.40952;,
 3.46092;-12.38469;-2.76515;;
 
 56;
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
 4;40,41,42,43;,
 4;40,43,44,45;,
 4;43,42,46,47;,
 4;43,47,10,44;,
 4;48,49,50,51;,
 4;48,51,52,53;,
 4;51,50,54,55;,
 4;51,55,22,52;,
 4;56,0,2,57;,
 4;56,57,3,5;,
 4;58,6,8,59;,
 4;58,59,12,14;,
 4;60,9,11,61;,
 4;60,61,18,20;,
 4;62,15,17,63;,
 4;62,63,21,23;,
 4;64,65,66,67;,
 4;64,67,68,69;,
 4;67,66,3,70;,
 4;67,70,71,68;,
 4;72,73,74,75;,
 4;72,75,76,77;,
 4;75,74,21,78;,
 4;75,78,79,76;,
 4;80,81,82,83;,
 4;80,83,84,85;,
 4;83,82,18,86;,
 4;83,86,87,84;,
 4;88,89,90,91;,
 4;88,91,92,93;,
 4;91,90,12,94;,
 4;91,94,95,92;;
 
 MeshMaterialList {
  10;
  56;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
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
   0.178824;0.156863;0.090980;1.000000;;
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
 }
 MeshNormals {
  54;
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
  0.000000;-1.000000;-0.000000;;
  56;
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
  4;53,46,9,35;;
 }
 MeshTextureCoords {
  96;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.495200;,
  1.000000;1.000000;,
  0.485670;1.000000;,
  0.485670;0.494220;,
  0.485670;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.495200;,
  1.000000;0.495200;,
  1.000000;1.000000;,
  0.514330;1.000000;,
  0.514330;0.494220;,
  0.514330;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;0.495200;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.494000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.485670;,
  0.492790;0.485670;,
  1.000000;0.485670;,
  1.000000;1.000000;,
  0.494000;0.000000;,
  1.000000;0.000000;,
  0.494000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.514330;,
  0.492790;0.514330;,
  1.000000;0.514330;,
  1.000000;1.000000;,
  0.494000;0.000000;,
  1.000000;0.000000;,
  0.494000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.495200;,
  0.494000;0.495200;,
  1.000000;0.495200;,
  1.000000;1.000000;,
  0.494000;0.000000;,
  1.000000;0.000000;,
  0.494000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.504800;,
  0.494000;0.504800;,
  1.000000;0.504800;,
  1.000000;1.000000;,
  0.494000;0.000000;,
  1.000000;0.000000;;
 }
}
