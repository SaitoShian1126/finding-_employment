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
 199;
 3.51072;0.14526;-2.89210;,
 3.85703;0.12316;-2.89210;,
 3.51072;0.12316;-3.16878;,
 4.15062;0.06024;-2.89210;,
 3.96320;0.06024;-3.25360;,
 3.51072;0.06024;-3.40335;,
 4.34679;-0.03394;-2.89210;,
 4.23478;-0.03394;-3.22609;,
 3.92875;-0.03394;-3.47059;,
 3.51072;-0.03394;-3.56008;,
 4.41567;-0.14501;-2.89210;,
 4.34679;-0.14501;-3.16878;,
 4.15062;-0.14501;-3.40335;,
 3.85703;-0.14501;-3.56008;,
 3.51072;-0.14501;-3.61512;,
 -3.72889;0.12316;-3.16878;,
 -4.07520;0.12316;-2.89210;,
 -3.72889;0.14526;-2.89210;,
 -4.18136;0.06024;-3.25360;,
 -4.36879;0.06024;-2.89210;,
 -3.72889;0.06024;-3.40335;,
 -4.45295;-0.03394;-3.22609;,
 -4.56496;-0.03394;-2.89210;,
 -4.14692;-0.03394;-3.47059;,
 -3.72889;-0.03394;-3.56008;,
 -4.56496;-0.14501;-3.16878;,
 -4.63384;-0.14501;-2.89210;,
 -4.36879;-0.14501;-3.40335;,
 -4.07520;-0.14501;-3.56008;,
 -3.72889;-0.14501;-3.61512;,
 2.57453;-2.70329;-2.34924;,
 2.83128;-2.70329;-2.14412;,
 2.57453;-2.71965;-2.14412;,
 2.90999;-2.65663;-2.41213;,
 3.04894;-2.65663;-2.14412;,
 2.57453;-2.65663;-2.52315;,
 3.11133;-2.58682;-2.39173;,
 3.19437;-2.58682;-2.14412;,
 2.88445;-2.58682;-2.57300;,
 2.57453;-2.58682;-2.63934;,
 3.19437;-2.50447;-2.34924;,
 3.24544;-2.50447;-2.14412;,
 3.04894;-2.50447;-2.52315;,
 2.83128;-2.50447;-2.63934;,
 2.57453;-2.50447;-2.68015;,
 3.51072;0.12316;3.16878;,
 3.85703;0.12316;2.89210;,
 3.51072;0.14526;2.89210;,
 3.96320;0.06024;3.25360;,
 4.15062;0.06024;2.89210;,
 3.51072;0.06024;3.40335;,
 4.23478;-0.03394;3.22609;,
 4.34679;-0.03394;2.89210;,
 3.92875;-0.03394;3.47059;,
 3.51072;-0.03394;3.56008;,
 4.34679;-0.14501;3.16878;,
 4.41567;-0.14501;2.89210;,
 4.15062;-0.14501;3.40335;,
 3.85703;-0.14501;3.56008;,
 3.51072;-0.14501;3.61512;,
 -2.79270;-2.71965;-2.14412;,
 -3.04945;-2.70329;-2.14412;,
 -2.79270;-2.70329;-2.34924;,
 -3.26711;-2.65663;-2.14412;,
 -3.12815;-2.65663;-2.41213;,
 -2.79270;-2.65663;-2.52315;,
 -3.41254;-2.58682;-2.14412;,
 -3.32950;-2.58682;-2.39173;,
 -3.10262;-2.58682;-2.57300;,
 -2.79270;-2.58682;-2.63934;,
 -3.46361;-2.50447;-2.14412;,
 -3.41254;-2.50447;-2.34924;,
 -3.26711;-2.50447;-2.52315;,
 -3.04945;-2.50447;-2.63934;,
 -2.79270;-2.50447;-2.68015;,
 2.57453;-2.71965;2.14412;,
 2.83128;-2.70329;2.14412;,
 2.57453;-2.70329;2.34924;,
 3.04894;-2.65663;2.14412;,
 2.90999;-2.65663;2.41213;,
 2.57453;-2.65663;2.52315;,
 3.19437;-2.58682;2.14412;,
 3.11133;-2.58682;2.39173;,
 2.88445;-2.58682;2.57300;,
 2.57453;-2.58682;2.63934;,
 3.24544;-2.50447;2.14412;,
 3.19437;-2.50447;2.34924;,
 3.04894;-2.50447;2.52315;,
 2.83128;-2.50447;2.63934;,
 2.57453;-2.50447;2.68015;,
 -3.72889;0.14526;2.89210;,
 -4.07520;0.12316;2.89210;,
 -3.72889;0.12316;3.16878;,
 -4.36879;0.06024;2.89210;,
 -4.18136;0.06024;3.25360;,
 -3.72889;0.06024;3.40335;,
 -4.56496;-0.03394;2.89210;,
 -4.45295;-0.03394;3.22609;,
 -4.14692;-0.03394;3.47059;,
 -3.72889;-0.03394;3.56008;,
 -4.63384;-0.14501;2.89210;,
 -4.56496;-0.14501;3.16878;,
 -4.36879;-0.14501;3.40335;,
 -4.07520;-0.14501;3.56008;,
 -3.72889;-0.14501;3.61512;,
 -2.79270;-2.70329;2.34924;,
 -3.04945;-2.70329;2.14412;,
 -2.79270;-2.71965;2.14412;,
 -3.12815;-2.65663;2.41213;,
 -3.26711;-2.65663;2.14412;,
 -2.79270;-2.65663;2.52315;,
 -3.32950;-2.58682;2.39173;,
 -3.41254;-2.58682;2.14412;,
 -3.10262;-2.58682;2.57300;,
 -2.79270;-2.58682;2.63934;,
 -3.41254;-2.50447;2.34924;,
 -3.46361;-2.50447;2.14412;,
 -3.26711;-2.50447;2.52315;,
 -3.04945;-2.50447;2.63934;,
 -2.79270;-2.50447;2.68015;,
 3.24979;-1.29880;-3.35453;,
 3.57114;-1.29880;-3.30346;,
 3.84357;-1.29880;-3.15803;,
 4.02560;-1.29880;-2.94036;,
 4.08951;-1.29880;-2.68363;,
 3.24979;-1.29880;3.35453;,
 3.57114;-1.29880;3.30346;,
 3.84357;-1.29880;3.15803;,
 4.02560;-1.29880;2.94036;,
 4.08951;-1.29880;2.68363;,
 -3.46796;-1.29880;-3.35453;,
 -3.78931;-1.29880;-3.30346;,
 -4.06174;-1.29880;-3.15803;,
 -4.24377;-1.29880;-2.94036;,
 -4.30768;-1.29880;-2.68363;,
 -3.46796;-1.29880;3.35453;,
 -3.78931;-1.29880;3.30346;,
 -4.06174;-1.29880;3.15803;,
 -4.24377;-1.29880;2.94036;,
 -4.30768;-1.29880;2.68363;,
 4.20111;0.14526;-0.00874;,
 4.61348;0.12316;-0.00874;,
 4.96306;0.06024;-0.00874;,
 5.19664;-0.03394;-0.00874;,
 5.27866;-0.14501;-0.00874;,
 3.08637;-2.71965;-0.00874;,
 3.39208;-2.70329;-0.00874;,
 3.65126;-2.65663;-0.00874;,
 3.82443;-2.58682;-0.00874;,
 3.88524;-2.50447;-0.00874;,
 -4.41928;0.14526;-0.00874;,
 -4.83164;0.12316;-0.00874;,
 -5.18123;0.06024;-0.00874;,
 -5.41481;-0.03394;-0.00874;,
 -5.49683;-0.14501;-0.00874;,
 -3.30454;-2.71965;-0.00874;,
 -3.61025;-2.70329;-0.00874;,
 -3.86943;-2.65663;-0.00874;,
 -4.04260;-2.58682;-0.00874;,
 -4.10341;-2.50447;-0.00874;,
 4.89029;-1.29880;-0.00874;,
 -5.10846;-1.29880;-0.00874;,
 0.02685;0.14526;-3.46092;,
 0.02685;0.12316;-3.79202;,
 -3.72889;0.12316;-3.16878;,
 -3.72889;0.14526;-2.89210;,
 0.02685;0.06024;-4.07272;,
 -3.72889;0.06024;-3.40335;,
 0.02685;-0.03394;-4.26028;,
 -3.72889;-0.03394;-3.56008;,
 0.02685;-0.14501;-4.32614;,
 -3.72889;-0.14501;-3.61512;,
 0.02685;-2.70329;-2.81129;,
 0.02685;-2.71965;-2.56583;,
 -2.79270;-2.71965;-2.14412;,
 -2.79270;-2.70329;-2.34924;,
 0.02685;-2.65663;-3.01940;,
 -2.79270;-2.65663;-2.52315;,
 0.02685;-2.58682;-3.15845;,
 -2.79270;-2.58682;-2.63934;,
 0.02685;-2.50447;-3.20728;,
 -2.79270;-2.50447;-2.68015;,
 0.02685;0.12316;3.79202;,
 0.02685;0.14526;3.46092;,
 0.02685;0.06024;4.07272;,
 0.02685;-0.03394;4.26028;,
 0.02685;-0.14501;4.32614;,
 0.02685;-2.71965;2.56583;,
 0.02685;-2.70329;2.81129;,
 0.02685;-2.65663;3.01940;,
 0.02685;-2.58682;3.15845;,
 0.02685;-2.50447;3.20728;,
 -3.46796;-1.29880;-3.35453;,
 0.02685;-1.29880;-4.01430;,
 0.02685;-1.29880;4.01430;,
 -4.41928;0.14526;-0.00874;,
 0.02685;0.14526;-0.00874;,
 0.02685;-2.71965;-0.00874;,
 -3.30454;-2.71965;-0.00874;;
 
 248;
 3;0,1,2;,
 3;1,3,4;,
 3;4,2,1;,
 3;2,4,5;,
 3;3,6,7;,
 3;7,4,3;,
 3;4,7,8;,
 3;8,5,4;,
 3;5,8,9;,
 3;6,10,11;,
 3;11,7,6;,
 3;7,11,12;,
 3;12,8,7;,
 3;8,12,13;,
 3;13,9,8;,
 3;9,13,14;,
 3;15,16,17;,
 3;18,19,16;,
 3;16,15,18;,
 3;20,18,15;,
 3;21,22,19;,
 3;19,18,21;,
 3;23,21,18;,
 3;18,20,23;,
 3;24,23,20;,
 3;25,26,22;,
 3;22,21,25;,
 3;27,25,21;,
 3;21,23,27;,
 3;28,27,23;,
 3;23,24,28;,
 3;29,28,24;,
 3;30,31,32;,
 3;33,34,31;,
 3;31,30,33;,
 3;35,33,30;,
 3;36,37,34;,
 3;34,33,36;,
 3;38,36,33;,
 3;33,35,38;,
 3;39,38,35;,
 3;40,41,37;,
 3;37,36,40;,
 3;42,40,36;,
 3;36,38,42;,
 3;43,42,38;,
 3;38,39,43;,
 3;44,43,39;,
 3;45,46,47;,
 3;48,49,46;,
 3;46,45,48;,
 3;50,48,45;,
 3;51,52,49;,
 3;49,48,51;,
 3;53,51,48;,
 3;48,50,53;,
 3;54,53,50;,
 3;55,56,52;,
 3;52,51,55;,
 3;57,55,51;,
 3;51,53,57;,
 3;58,57,53;,
 3;53,54,58;,
 3;59,58,54;,
 3;60,61,62;,
 3;61,63,64;,
 3;64,62,61;,
 3;62,64,65;,
 3;63,66,67;,
 3;67,64,63;,
 3;64,67,68;,
 3;68,65,64;,
 3;65,68,69;,
 3;66,70,71;,
 3;71,67,66;,
 3;67,71,72;,
 3;72,68,67;,
 3;68,72,73;,
 3;73,69,68;,
 3;69,73,74;,
 3;75,76,77;,
 3;76,78,79;,
 3;79,77,76;,
 3;77,79,80;,
 3;78,81,82;,
 3;82,79,78;,
 3;79,82,83;,
 3;83,80,79;,
 3;80,83,84;,
 3;81,85,86;,
 3;86,82,81;,
 3;82,86,87;,
 3;87,83,82;,
 3;83,87,88;,
 3;88,84,83;,
 3;84,88,89;,
 3;90,91,92;,
 3;91,93,94;,
 3;94,92,91;,
 3;92,94,95;,
 3;93,96,97;,
 3;97,94,93;,
 3;94,97,98;,
 3;98,95,94;,
 3;95,98,99;,
 3;96,100,101;,
 3;101,97,96;,
 3;97,101,102;,
 3;102,98,97;,
 3;98,102,103;,
 3;103,99,98;,
 3;99,103,104;,
 3;105,106,107;,
 3;108,109,106;,
 3;106,105,108;,
 3;110,108,105;,
 3;111,112,109;,
 3;109,108,111;,
 3;113,111,108;,
 3;108,110,113;,
 3;114,113,110;,
 3;115,116,112;,
 3;112,111,115;,
 3;117,115,111;,
 3;111,113,117;,
 3;118,117,113;,
 3;113,114,118;,
 3;119,118,114;,
 4;120,14,13,121;,
 4;120,121,43,44;,
 4;121,13,12,122;,
 4;121,122,42,43;,
 4;122,12,11,123;,
 4;122,123,40,42;,
 4;123,11,10,124;,
 4;123,124,41,40;,
 4;125,89,88,126;,
 4;125,126,58,59;,
 4;126,88,87,127;,
 4;126,127,57,58;,
 4;127,87,86,128;,
 4;127,128,55,57;,
 4;128,86,85,129;,
 4;128,129,56,55;,
 4;130,74,73,131;,
 4;130,131,28,29;,
 4;131,73,72,132;,
 4;131,132,27,28;,
 4;132,72,71,133;,
 4;132,133,25,27;,
 4;133,71,70,134;,
 4;133,134,26,25;,
 4;135,104,103,136;,
 4;135,136,118,119;,
 4;136,103,102,137;,
 4;136,137,117,118;,
 4;137,102,101,138;,
 4;137,138,115,117;,
 4;138,101,100,139;,
 4;138,139,116,115;,
 4;140,47,46,141;,
 4;140,141,1,0;,
 4;141,46,49,142;,
 4;141,142,3,1;,
 4;142,49,52,143;,
 4;142,143,6,3;,
 4;143,52,56,144;,
 4;143,144,10,6;,
 4;145,32,31,146;,
 4;145,146,76,75;,
 4;146,31,34,147;,
 4;146,147,78,76;,
 4;147,34,37,148;,
 4;147,148,81,78;,
 4;148,37,41,149;,
 4;148,149,85,81;,
 4;150,17,16,151;,
 4;150,151,91,90;,
 4;151,16,19,152;,
 4;151,152,93,91;,
 4;152,19,22,153;,
 4;152,153,96,93;,
 4;153,22,26,154;,
 4;153,154,100,96;,
 4;155,107,106,156;,
 4;155,156,61,60;,
 4;156,106,109,157;,
 4;156,157,63,61;,
 4;157,109,112,158;,
 4;157,158,66,63;,
 4;158,112,116,159;,
 4;158,159,70,66;,
 4;149,41,124,160;,
 4;149,160,129,85;,
 4;160,124,10,144;,
 4;160,144,56,129;,
 4;154,26,134,161;,
 4;154,161,139,100;,
 4;161,134,70,159;,
 4;161,159,116,139;,
 4;162,0,2,163;,
 4;162,163,164,165;,
 4;163,2,5,166;,
 4;163,166,167,164;,
 4;166,5,9,168;,
 4;166,168,169,167;,
 4;168,9,14,170;,
 4;168,170,171,169;,
 4;172,30,32,173;,
 4;172,173,174,175;,
 4;176,35,30,172;,
 4;176,172,175,177;,
 4;178,39,35,176;,
 4;178,176,177,179;,
 4;180,44,39,178;,
 4;180,178,179,181;,
 4;182,45,47,183;,
 4;182,183,90,92;,
 4;184,50,45,182;,
 4;184,182,92,95;,
 4;185,54,50,184;,
 4;185,184,95,99;,
 4;186,59,54,185;,
 4;186,185,99,104;,
 4;187,75,77,188;,
 4;187,188,105,107;,
 4;188,77,80,189;,
 4;188,189,110,105;,
 4;189,80,84,190;,
 4;189,190,114,110;,
 4;190,84,89,191;,
 4;190,191,119,114;,
 4;180,181,192,193;,
 4;180,193,120,44;,
 4;193,192,171,170;,
 4;193,170,14,120;,
 4;186,104,135,194;,
 4;186,194,125,59;,
 4;194,135,119,191;,
 4;194,191,89,125;,
 4;162,165,195,196;,
 4;162,196,140,0;,
 4;196,195,90,183;,
 4;196,183,47,140;,
 4;187,107,155,197;,
 4;187,197,145,75;,
 4;197,198,174,173;,
 4;197,173,32,145;;
 
 MeshMaterialList {
  10;
  248;
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
  186;
  -0.033443;0.998565;0.041823;,
  0.033668;0.998558;0.041822;,
  -0.033442;0.998564;-0.041845;,
  0.033668;0.998557;-0.041845;,
  -0.170034;0.108196;-0.979480;,
  0.177091;0.107711;-0.978283;,
  -0.147332;-0.500320;-0.853213;,
  0.155031;-0.500371;-0.851818;,
  -0.033357;-0.998569;-0.041788;,
  0.033661;-0.998559;-0.041788;,
  -0.033357;-0.998571;0.041758;,
  0.033661;-0.998560;0.041758;,
  -0.147332;-0.500320;0.853213;,
  0.155031;-0.500371;0.851818;,
  -0.170034;0.108196;0.979480;,
  0.177091;0.107711;0.978283;,
  0.957370;0.124237;0.260784;,
  0.788146;-0.576890;0.214533;,
  0.957157;0.124184;-0.261589;,
  0.787956;-0.576836;-0.215373;,
  -0.788145;-0.576890;0.214533;,
  -0.957370;0.124237;0.260784;,
  -0.787951;-0.576843;-0.215372;,
  -0.957157;0.124186;-0.261589;,
  -0.062688;0.985411;-0.158226;,
  0.063507;0.985360;-0.158215;,
  -0.092739;0.918905;-0.383422;,
  0.094742;0.918734;-0.383342;,
  -0.140109;0.659281;-0.738728;,
  0.144063;0.658946;-0.738265;,
  -0.062546;-0.985422;-0.158214;,
  0.063652;-0.985353;-0.158200;,
  -0.092413;-0.918938;-0.383422;,
  0.095118;-0.918708;-0.383313;,
  -0.139471;-0.659346;-0.738790;,
  0.144810;-0.658895;-0.738165;,
  -0.062688;0.985411;0.158226;,
  0.063507;0.985360;0.158215;,
  -0.092739;0.918905;0.383422;,
  0.094742;0.918734;0.383342;,
  -0.140109;0.659281;0.738728;,
  0.144063;0.658946;0.738265;,
  -0.062546;-0.985422;0.158214;,
  0.063652;-0.985353;0.158200;,
  -0.092413;-0.918938;0.383422;,
  0.095118;-0.918708;0.383313;,
  -0.139471;-0.659346;0.738790;,
  0.144810;-0.658895;0.738165;,
  0.127250;0.988736;0.078799;,
  0.127249;0.988729;-0.078880;,
  0.315751;0.941287;0.119501;,
  0.315742;0.941264;-0.119702;,
  0.664228;0.721078;0.197098;,
  0.664163;0.721022;-0.197521;,
  0.127240;-0.988739;0.078773;,
  0.127239;-0.988730;-0.078882;,
  0.315741;-0.941295;0.119463;,
  0.315729;-0.941264;-0.119734;,
  0.664229;-0.721097;0.197026;,
  0.664141;-0.721022;-0.197596;,
  -0.127250;0.988735;0.078800;,
  -0.127249;0.988729;-0.078881;,
  -0.315748;0.941287;0.119503;,
  -0.315739;0.941265;-0.119704;,
  -0.664228;0.721078;0.197098;,
  -0.664163;0.721022;-0.197521;,
  -0.127241;-0.988739;0.078776;,
  -0.127239;-0.988730;-0.078884;,
  -0.315738;-0.941296;0.119465;,
  -0.315726;-0.941265;-0.119736;,
  -0.664229;-0.721097;0.197026;,
  -0.664140;-0.721023;-0.197596;,
  0.254864;-0.509861;-0.821636;,
  0.294275;0.176907;-0.939205;,
  0.528311;-0.540673;-0.654645;,
  0.619610;0.170517;-0.766164;,
  0.740330;-0.572778;-0.351904;,
  0.882622;0.205841;-0.422621;,
  0.254864;-0.509861;0.821636;,
  0.294275;0.176907;0.939205;,
  0.528311;-0.540673;0.654645;,
  0.619610;0.170517;0.766164;,
  0.740330;-0.572778;0.351904;,
  0.882622;0.205841;0.422621;,
  -0.254864;-0.509861;-0.821636;,
  -0.294275;0.176907;-0.939205;,
  -0.528311;-0.540674;-0.654645;,
  -0.619610;0.170517;-0.766164;,
  -0.740330;-0.572779;-0.351904;,
  -0.882622;0.205842;-0.422621;,
  -0.254864;-0.509861;0.821636;,
  -0.294275;0.176907;0.939205;,
  -0.528311;-0.540674;0.654645;,
  -0.619610;0.170517;0.766164;,
  -0.740330;-0.572779;0.351904;,
  -0.882622;0.205842;0.422621;,
  0.205359;0.944696;-0.255691;,
  0.533096;0.753679;-0.384418;,
  0.294192;0.720771;-0.627647;,
  -0.205356;0.944697;-0.255689;,
  -0.533092;0.753682;-0.384416;,
  -0.294191;0.720773;-0.627644;,
  0.205357;-0.944697;-0.255687;,
  0.533090;-0.753692;-0.384401;,
  0.294184;-0.720781;-0.627639;,
  0.205359;0.944696;0.255691;,
  0.533096;0.753679;0.384418;,
  0.294192;0.720771;0.627647;,
  -0.205353;-0.944699;-0.255685;,
  -0.533085;-0.753696;-0.384400;,
  -0.294182;-0.720785;-0.627635;,
  0.205357;-0.944697;0.255687;,
  0.533090;-0.753692;0.384401;,
  0.294184;-0.720781;0.627639;,
  -0.205356;0.944697;0.255689;,
  -0.533092;0.753682;0.384416;,
  -0.294191;0.720773;0.627644;,
  -0.205353;-0.944699;0.255685;,
  -0.533085;-0.753696;0.384400;,
  -0.294182;-0.720785;0.627635;,
  -0.156534;-0.403634;-0.901430;,
  0.163643;-0.404226;-0.899901;,
  -0.156534;-0.403634;0.901430;,
  0.163643;-0.404226;0.899901;,
  0.851037;-0.470918;0.232319;,
  0.850819;-0.470925;-0.233104;,
  -0.851037;-0.470918;0.232319;,
  -0.850816;-0.470931;-0.233103;,
  0.283781;-0.436440;-0.853808;,
  0.550401;-0.484376;-0.680028;,
  0.777926;-0.489819;-0.393583;,
  0.283781;-0.436440;0.853808;,
  0.550401;-0.484376;0.680028;,
  0.777926;-0.489819;0.393583;,
  -0.283781;-0.436440;-0.853808;,
  -0.550401;-0.484376;-0.680028;,
  -0.777926;-0.489819;-0.393583;,
  -0.283781;-0.436440;0.853808;,
  -0.550401;-0.484376;0.680028;,
  -0.777926;-0.489819;0.393583;,
  -0.029312;0.999570;-0.000022;,
  0.029312;0.999570;-0.000022;,
  -0.029269;-0.999572;-0.000030;,
  0.029269;-0.999572;-0.000030;,
  0.990523;0.137342;-0.000844;,
  0.798892;-0.601474;-0.000858;,
  -0.798887;-0.601480;-0.000857;,
  -0.990523;0.137343;-0.000845;,
  0.126236;0.992000;-0.000101;,
  0.300016;0.953934;-0.000253;,
  0.638118;0.769938;-0.000541;,
  0.126217;-0.992003;-0.000136;,
  0.300011;-0.953936;-0.000341;,
  0.638096;-0.769956;-0.000730;,
  -0.126235;0.992000;-0.000101;,
  -0.300015;0.953934;-0.000253;,
  -0.638118;0.769938;-0.000541;,
  -0.126217;-0.992003;-0.000136;,
  -0.300011;-0.953936;-0.000341;,
  -0.638096;-0.769956;-0.000730;,
  0.872260;-0.489042;-0.000807;,
  -0.872256;-0.489048;-0.000806;,
  0.000226;0.999331;0.036579;,
  0.000226;0.999331;-0.036579;,
  0.007198;0.117191;-0.993083;,
  0.007779;-0.517399;-0.855709;,
  0.000304;-0.999333;-0.036526;,
  0.000304;-0.999333;0.036526;,
  0.007779;-0.517399;0.855709;,
  0.007198;0.117191;0.993083;,
  0.001027;0.987669;-0.156550;,
  0.002517;0.931588;-0.363508;,
  0.005022;0.706212;-0.707983;,
  0.001387;-0.987673;-0.156525;,
  0.003399;-0.931587;-0.363503;,
  0.006781;-0.706234;-0.707946;,
  0.001027;0.987669;0.156550;,
  0.002517;0.931588;0.363508;,
  0.005022;0.706212;0.707983;,
  0.001387;-0.987673;0.156525;,
  0.003399;-0.931587;0.363503;,
  0.006781;-0.706234;0.707946;,
  0.007198;-0.414445;-0.910046;,
  0.007198;-0.414445;0.910046;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  248;
  3;3,49,25;,
  3;49,51,96;,
  3;96,25,49;,
  3;25,96,27;,
  3;51,53,97;,
  3;97,96,51;,
  3;96,97,98;,
  3;98,27,96;,
  3;27,98,29;,
  3;53,18,77;,
  3;77,97,53;,
  3;97,77,75;,
  3;75,98,97;,
  3;98,75,73;,
  3;73,29,98;,
  3;29,73,5;,
  3;24,61,2;,
  3;99,63,61;,
  3;61,24,99;,
  3;26,99,24;,
  3;100,65,63;,
  3;63,99,100;,
  3;101,100,99;,
  3;99,26,101;,
  3;28,101,26;,
  3;89,23,65;,
  3;65,100,89;,
  3;87,89,100;,
  3;100,101,87;,
  3;85,87,101;,
  3;101,28,85;,
  3;4,85,28;,
  3;31,55,9;,
  3;102,57,55;,
  3;55,31,102;,
  3;33,102,31;,
  3;103,59,57;,
  3;57,102,103;,
  3;104,103,102;,
  3;102,33,104;,
  3;35,104,33;,
  3;76,19,59;,
  3;59,103,76;,
  3;74,76,103;,
  3;103,104,74;,
  3;72,74,104;,
  3;104,35,72;,
  3;7,72,35;,
  3;37,48,1;,
  3;105,50,48;,
  3;48,37,105;,
  3;39,105,37;,
  3;106,52,50;,
  3;50,105,106;,
  3;107,106,105;,
  3;105,39,107;,
  3;41,107,39;,
  3;83,16,52;,
  3;52,106,83;,
  3;81,83,106;,
  3;106,107,81;,
  3;79,81,107;,
  3;107,41,79;,
  3;15,79,41;,
  3;8,67,30;,
  3;67,69,108;,
  3;108,30,67;,
  3;30,108,32;,
  3;69,71,109;,
  3;109,108,69;,
  3;108,109,110;,
  3;110,32,108;,
  3;32,110,34;,
  3;71,22,88;,
  3;88,109,71;,
  3;109,88,86;,
  3;86,110,109;,
  3;110,86,84;,
  3;84,34,110;,
  3;34,84,6;,
  3;11,54,43;,
  3;54,56,111;,
  3;111,43,54;,
  3;43,111,45;,
  3;56,58,112;,
  3;112,111,56;,
  3;111,112,113;,
  3;113,45,111;,
  3;45,113,47;,
  3;58,17,82;,
  3;82,112,58;,
  3;112,82,80;,
  3;80,113,112;,
  3;113,80,78;,
  3;78,47,113;,
  3;47,78,13;,
  3;0,60,36;,
  3;60,62,114;,
  3;114,36,60;,
  3;36,114,38;,
  3;62,64,115;,
  3;115,114,62;,
  3;114,115,116;,
  3;116,38,114;,
  3;38,116,40;,
  3;64,21,95;,
  3;95,115,64;,
  3;115,95,93;,
  3;93,116,115;,
  3;116,93,91;,
  3;91,40,116;,
  3;40,91,14;,
  3;42,66,10;,
  3;117,68,66;,
  3;66,42,117;,
  3;44,117,42;,
  3;118,70,68;,
  3;68,117,118;,
  3;119,118,117;,
  3;117,44,119;,
  3;46,119,44;,
  3;94,20,70;,
  3;70,118,94;,
  3;92,94,118;,
  3;118,119,92;,
  3;90,92,119;,
  3;119,46,90;,
  3;12,90,46;,
  4;121,5,73,128;,
  4;121,128,72,7;,
  4;128,73,75,129;,
  4;128,129,74,72;,
  4;129,75,77,130;,
  4;129,130,76,74;,
  4;130,77,18,125;,
  4;130,125,19,76;,
  4;123,13,78,131;,
  4;123,131,79,15;,
  4;131,78,80,132;,
  4;131,132,81,79;,
  4;132,80,82,133;,
  4;132,133,83,81;,
  4;133,82,17,124;,
  4;133,124,16,83;,
  4;120,6,84,134;,
  4;120,134,85,4;,
  4;134,84,86,135;,
  4;134,135,87,85;,
  4;135,86,88,136;,
  4;135,136,89,87;,
  4;136,88,22,127;,
  4;136,127,23,89;,
  4;122,14,91,137;,
  4;122,137,90,12;,
  4;137,91,93,138;,
  4;137,138,92,90;,
  4;138,93,95,139;,
  4;138,139,94,92;,
  4;139,95,21,126;,
  4;139,126,20,94;,
  4;141,1,48,148;,
  4;141,148,49,3;,
  4;148,48,50,149;,
  4;148,149,51,49;,
  4;149,50,52,150;,
  4;149,150,53,51;,
  4;150,52,16,144;,
  4;150,144,18,53;,
  4;143,9,55,151;,
  4;143,151,54,11;,
  4;151,55,57,152;,
  4;151,152,56,54;,
  4;152,57,59,153;,
  4;152,153,58,56;,
  4;153,59,19,145;,
  4;153,145,17,58;,
  4;140,2,61,154;,
  4;140,154,60,0;,
  4;154,61,63,155;,
  4;154,155,62,60;,
  4;155,63,65,156;,
  4;155,156,64,62;,
  4;156,65,23,147;,
  4;156,147,21,64;,
  4;142,10,66,157;,
  4;142,157,67,8;,
  4;157,66,68,158;,
  4;157,158,69,67;,
  4;158,68,70,159;,
  4;158,159,71,69;,
  4;159,70,20,146;,
  4;159,146,22,71;,
  4;145,19,125,160;,
  4;145,160,124,17;,
  4;160,125,18,144;,
  4;160,144,16,124;,
  4;147,23,127,161;,
  4;147,161,126,21;,
  4;161,127,22,146;,
  4;161,146,20,126;,
  4;163,3,25,170;,
  4;163,170,24,2;,
  4;170,25,27,171;,
  4;170,171,26,24;,
  4;171,27,29,172;,
  4;171,172,28,26;,
  4;172,29,5,164;,
  4;172,164,4,28;,
  4;173,31,9,166;,
  4;173,166,8,30;,
  4;174,33,31,173;,
  4;174,173,30,32;,
  4;175,35,33,174;,
  4;175,174,32,34;,
  4;165,7,35,175;,
  4;165,175,34,6;,
  4;176,37,1,162;,
  4;176,162,0,36;,
  4;177,39,37,176;,
  4;177,176,36,38;,
  4;178,41,39,177;,
  4;178,177,38,40;,
  4;169,15,41,178;,
  4;169,178,40,14;,
  4;167,11,43,179;,
  4;167,179,42,10;,
  4;179,43,45,180;,
  4;179,180,44,42;,
  4;180,45,47,181;,
  4;180,181,46,44;,
  4;181,47,13,168;,
  4;181,168,12,46;,
  4;165,6,120,182;,
  4;165,182,121,7;,
  4;182,120,4,164;,
  4;182,164,5,121;,
  4;169,14,122,183;,
  4;169,183,123,15;,
  4;183,122,12,168;,
  4;183,168,13,123;,
  4;163,2,140,184;,
  4;163,184,141,3;,
  4;184,140,0,162;,
  4;184,162,1,141;,
  4;167,10,142,185;,
  4;167,185,143,11;,
  4;185,142,8,166;,
  4;185,166,9,143;;
 }
 MeshTextureCoords {
  199;
  0.140329;0.492737;,
  0.147601;0.493842;,
  0.133140;0.493842;,
  0.153144;0.496988;,
  0.140599;0.496988;,
  0.127471;0.496988;,
  0.156563;0.501697;,
  0.146388;0.501697;,
  0.134842;0.501697;,
  0.123889;0.501697;,
  0.157713;0.507250;,
  0.149745;0.507250;,
  0.140693;0.507250;,
  0.131368;0.507250;,
  0.122668;0.507250;,
  0.862104;0.493842;,
  0.848230;0.493842;,
  0.854991;0.492737;,
  0.855242;0.496988;,
  0.843067;0.496988;,
  0.867741;0.496988;,
  0.849785;0.501697;,
  0.839878;0.501697;,
  0.860906;0.501697;,
  0.871315;0.501697;,
  0.846574;0.507250;,
  0.838804;0.507250;,
  0.855331;0.507250;,
  0.864279;0.507250;,
  0.872535;0.507250;,
  0.132277;0.635164;,
  0.146843;0.635164;,
  0.139477;0.635983;,
  0.139845;0.632832;,
  0.152455;0.632832;,
  0.126604;0.632832;,
  0.145694;0.629341;,
  0.155916;0.629341;,
  0.134073;0.629341;,
  0.123022;0.629341;,
  0.149078;0.625224;,
  0.157081;0.625224;,
  0.139974;0.625224;,
  0.130582;0.625224;,
  0.121801;0.625224;,
  0.366860;0.493842;,
  0.352399;0.493842;,
  0.359671;0.492737;,
  0.359401;0.496988;,
  0.346856;0.496988;,
  0.372529;0.496988;,
  0.353612;0.501697;,
  0.343437;0.501697;,
  0.365158;0.501697;,
  0.376111;0.501697;,
  0.350255;0.507250;,
  0.342287;0.507250;,
  0.359307;0.507250;,
  0.368631;0.507250;,
  0.377332;0.507250;,
  0.854210;0.635983;,
  0.847533;0.635164;,
  0.861308;0.635164;,
  0.842433;0.632832;,
  0.854544;0.632832;,
  0.866937;0.632832;,
  0.839282;0.629341;,
  0.849143;0.629341;,
  0.860191;0.629341;,
  0.870508;0.629341;,
  0.838220;0.625224;,
  0.845956;0.625224;,
  0.854662;0.625224;,
  0.863546;0.625224;,
  0.871727;0.625224;,
  0.360523;0.635983;,
  0.353157;0.635164;,
  0.367723;0.635164;,
  0.347545;0.632832;,
  0.360155;0.632832;,
  0.373396;0.632832;,
  0.344084;0.629341;,
  0.354306;0.629341;,
  0.365927;0.629341;,
  0.376978;0.629341;,
  0.342919;0.625224;,
  0.350922;0.625224;,
  0.360026;0.625224;,
  0.369418;0.625224;,
  0.378199;0.625224;,
  0.645009;0.492737;,
  0.651770;0.493842;,
  0.637896;0.493842;,
  0.656933;0.496988;,
  0.644758;0.496988;,
  0.632259;0.496988;,
  0.660122;0.501697;,
  0.650215;0.501697;,
  0.639094;0.501697;,
  0.628685;0.501697;,
  0.661196;0.507250;,
  0.653426;0.507250;,
  0.644669;0.507250;,
  0.635721;0.507250;,
  0.627465;0.507250;,
  0.638692;0.635164;,
  0.652467;0.635164;,
  0.645790;0.635983;,
  0.645456;0.632832;,
  0.657567;0.632832;,
  0.633063;0.632832;,
  0.650857;0.629341;,
  0.660718;0.629341;,
  0.639809;0.629341;,
  0.629492;0.629341;,
  0.654044;0.625224;,
  0.661780;0.625224;,
  0.645338;0.625224;,
  0.636454;0.625224;,
  0.628273;0.625224;,
  0.122476;0.564940;,
  0.131194;0.564940;,
  0.140534;0.564940;,
  0.149597;0.564940;,
  0.157573;0.564940;,
  0.377524;0.564940;,
  0.368806;0.564940;,
  0.359466;0.564940;,
  0.350403;0.564940;,
  0.342427;0.564940;,
  0.872354;0.564940;,
  0.864115;0.564940;,
  0.855181;0.564940;,
  0.846435;0.564940;,
  0.838673;0.564940;,
  0.627646;0.564940;,
  0.635885;0.564940;,
  0.644819;0.564940;,
  0.653565;0.564940;,
  0.661327;0.564940;,
  0.249669;0.492737;,
  0.249698;0.493842;,
  0.249720;0.496988;,
  0.249732;0.501697;,
  0.249736;0.507250;,
  0.249549;0.635983;,
  0.249590;0.635164;,
  0.249619;0.632832;,
  0.249636;0.629341;,
  0.249642;0.625224;,
  0.750315;0.492737;,
  0.750288;0.493842;,
  0.750268;0.496988;,
  0.750257;0.501697;,
  0.750253;0.507250;,
  0.750421;0.635983;,
  0.750385;0.635164;,
  0.750359;0.632832;,
  0.750344;0.629341;,
  0.750339;0.625224;,
  0.249716;0.564940;,
  0.750272;0.564940;,
  0.001235;0.492737;,
  0.001127;0.493842;,
  -0.137896;0.493842;,
  -0.145009;0.492737;,
  0.001049;0.496988;,
  -0.132259;0.496988;,
  0.001003;0.501697;,
  -0.128685;0.501697;,
  0.000988;0.507250;,
  -0.127465;0.507250;,
  0.001520;0.635164;,
  0.001665;0.635983;,
  -0.145790;0.635983;,
  -0.138692;0.635164;,
  0.001415;0.632832;,
  -0.133063;0.632832;,
  0.001353;0.629341;,
  -0.129492;0.629341;,
  0.001332;0.625224;,
  -0.128273;0.625224;,
  0.498873;0.493842;,
  0.498765;0.492737;,
  0.498951;0.496988;,
  0.498997;0.501697;,
  0.499012;0.507250;,
  0.498335;0.635983;,
  0.498480;0.635164;,
  0.498585;0.632832;,
  0.498647;0.629341;,
  0.498668;0.625224;,
  -0.127646;0.564940;,
  0.001065;0.564940;,
  0.498935;0.564940;,
  -0.249685;0.492737;,
  0.199915;0.492737;,
  0.199915;0.635983;,
  -0.249579;0.635983;;
 }
}
