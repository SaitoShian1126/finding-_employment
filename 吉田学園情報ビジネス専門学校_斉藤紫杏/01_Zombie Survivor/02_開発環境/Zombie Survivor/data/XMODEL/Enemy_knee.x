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
 -0.00857;2.31473;0.00000;,
 0.57668;2.17717;-0.45155;,
 -0.00857;2.17717;-0.63859;,
 0.81910;2.17717;0.00000;,
 0.57668;2.17717;0.45155;,
 -0.00857;2.17717;0.63859;,
 -0.59381;2.17717;0.45155;,
 -0.83624;2.17717;0.00000;,
 -0.59381;2.17717;-0.45155;,
 1.07283;1.78540;-0.83435;,
 -0.00857;1.78540;-1.17996;,
 0.57668;2.17717;-0.45155;,
 1.52076;1.78540;0.00000;,
 1.07283;1.78540;-0.83435;,
 1.07283;1.78540;0.83435;,
 -0.00857;1.78540;1.17996;,
 -1.08997;1.78540;0.83435;,
 -1.53790;1.78540;0.00000;,
 -1.08997;1.78540;-0.83435;,
 1.40435;1.19903;-1.09014;,
 -0.00857;1.19903;-1.54169;,
 1.98960;1.19903;0.00000;,
 1.40435;1.19903;-1.09014;,
 1.40435;1.19903;1.09014;,
 -0.00857;1.19903;1.54169;,
 -1.42149;1.19903;1.09014;,
 -2.00674;1.19903;0.00000;,
 -1.42149;1.19903;-1.09014;,
 1.52076;0.50742;-1.17996;,
 -0.00857;0.50742;-1.66872;,
 2.15423;0.50742;0.00000;,
 1.52076;0.50742;-1.17996;,
 1.52076;0.50742;1.17996;,
 -0.00857;0.50742;1.66872;,
 -1.53790;0.50742;1.17996;,
 -2.17137;0.50742;0.00000;,
 -1.53790;0.50742;-1.17996;,
 1.40435;-0.18422;-1.09014;,
 -0.00857;-0.18422;-1.54169;,
 1.98960;-0.18422;-0.00000;,
 1.40435;-0.18422;-1.09014;,
 1.40435;-0.18422;1.09014;,
 -0.00857;-0.18422;1.54169;,
 -1.42149;-0.18422;1.09014;,
 -2.00674;-0.18422;0.00000;,
 -1.42149;-0.18422;-1.09014;,
 1.07283;-0.77057;-0.83435;,
 -0.00857;-0.77057;-1.17996;,
 1.52076;-0.77057;-0.00000;,
 1.07283;-0.77057;-0.83435;,
 1.07283;-0.77057;0.83435;,
 -0.00857;-0.77057;1.17996;,
 -1.08997;-0.77057;0.83435;,
 -1.53790;-0.77057;0.00000;,
 -1.08997;-0.77057;-0.83435;,
 0.57668;-1.16238;-0.45155;,
 -0.00857;-1.16238;-0.63859;,
 0.81910;-1.16238;-0.00000;,
 0.57668;-1.16238;-0.45155;,
 0.57668;-1.16238;0.45155;,
 -0.00857;-1.16238;0.63859;,
 -0.59381;-1.16238;0.45155;,
 -0.83624;-1.16238;0.00000;,
 -0.59381;-1.16238;-0.45155;,
 -0.00857;-1.29991;0.00000;,
 -0.00857;-1.29991;0.00000;;
 
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
  58;
  -0.000000;1.000000;0.000000;,
  -0.000001;0.914014;-0.405683;,
  0.228762;0.928983;-0.290961;,
  0.328218;0.944602;0.000000;,
  0.228762;0.928983;0.290961;,
  -0.000001;0.914014;0.405683;,
  -0.228761;0.928983;0.290962;,
  -0.328215;0.944603;0.000000;,
  -0.228761;0.928983;-0.290962;,
  -0.000000;0.681923;-0.731424;,
  0.434010;0.721393;-0.539655;,
  0.642753;0.766074;0.000000;,
  0.434010;0.721393;0.539655;,
  -0.000000;0.681923;0.731424;,
  -0.434009;0.721394;0.539655;,
  -0.642750;0.766076;0.000000;,
  -0.434009;0.721394;-0.539655;,
  0.000000;0.360004;-0.932951;,
  0.582901;0.396807;-0.709064;,
  0.896709;0.442621;0.000000;,
  0.582901;0.396807;0.709064;,
  0.000000;0.360004;0.932951;,
  -0.582901;0.396807;0.709064;,
  -0.896709;0.442621;0.000000;,
  -0.582901;0.396807;-0.709064;,
  0.000000;0.000004;-1.000000;,
  0.638394;0.000004;-0.769709;,
  1.000000;0.000005;0.000000;,
  0.638394;0.000004;0.769709;,
  0.000000;0.000004;1.000000;,
  -0.638394;0.000004;0.769709;,
  -1.000000;0.000005;0.000000;,
  -0.638394;0.000004;-0.769709;,
  0.000000;-0.360008;-0.932949;,
  0.582899;-0.396810;-0.709063;,
  0.896707;-0.442625;-0.000000;,
  0.582899;-0.396810;0.709063;,
  0.000000;-0.360008;0.932949;,
  -0.582899;-0.396810;0.709063;,
  -0.896707;-0.442625;0.000000;,
  -0.582899;-0.396810;-0.709063;,
  -0.000000;-0.681910;-0.731436;,
  0.434017;-0.721382;-0.539664;,
  0.642764;-0.766064;-0.000000;,
  0.434017;-0.721382;0.539664;,
  -0.000000;-0.681910;0.731436;,
  -0.434017;-0.721382;0.539664;,
  -0.642763;-0.766065;0.000000;,
  -0.434017;-0.721382;-0.539664;,
  -0.000001;-0.914013;-0.405684;,
  0.228764;-0.928982;-0.290962;,
  0.328221;-0.944601;-0.000000;,
  0.228764;-0.928982;0.290962;,
  -0.000001;-0.914013;0.405684;,
  -0.228763;-0.928982;0.290964;,
  -0.328219;-0.944601;0.000000;,
  -0.228763;-0.928982;-0.290964;,
  -0.000000;-1.000000;0.000000;;
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
  0.750000;0.384264;,
  1.144274;0.391142;,
  0.997864;0.391142;,
  0.250000;0.391142;,
  0.355726;0.391142;,
  0.502136;0.391142;,
  0.646527;0.391142;,
  0.750000;0.391142;,
  0.853473;0.391142;,
  1.144799;0.410730;,
  0.998844;0.410730;,
  0.144274;0.391142;,
  0.250000;0.410730;,
  0.144798;0.410730;,
  0.355202;0.410730;,
  0.501156;0.410730;,
  0.646019;0.410730;,
  0.750000;0.410730;,
  0.853981;0.410730;,
  1.144942;0.440049;,
  0.999115;0.440049;,
  0.250000;0.440049;,
  0.144942;0.440049;,
  0.355058;0.440049;,
  0.500885;0.440049;,
  0.645876;0.440049;,
  0.750000;0.440049;,
  0.854124;0.440049;,
  1.144978;0.474629;,
  0.999183;0.474629;,
  0.250000;0.474629;,
  0.144978;0.474629;,
  0.355022;0.474629;,
  0.500817;0.474629;,
  0.645841;0.474629;,
  0.750000;0.474629;,
  0.854159;0.474629;,
  1.144942;0.509211;,
  0.999115;0.509211;,
  0.250000;0.509211;,
  0.144942;0.509211;,
  0.355058;0.509211;,
  0.500885;0.509211;,
  0.645876;0.509211;,
  0.750000;0.509211;,
  0.854124;0.509211;,
  1.144799;0.538529;,
  0.998844;0.538529;,
  0.250000;0.538529;,
  0.144798;0.538529;,
  0.355202;0.538529;,
  0.501156;0.538529;,
  0.646019;0.538529;,
  0.750000;0.538529;,
  0.853981;0.538529;,
  1.144274;0.558119;,
  0.997864;0.558119;,
  0.250000;0.558119;,
  0.144274;0.558119;,
  0.355726;0.558119;,
  0.502136;0.558119;,
  0.646527;0.558119;,
  0.750000;0.558119;,
  0.853473;0.558119;,
  0.750000;0.564996;,
  -0.250000;0.564996;;
 }
}
