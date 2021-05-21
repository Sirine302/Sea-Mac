Heightmap opengl----------------
Url     : http://codes-sources.commentcamarche.net/source/24645-heightmap-openglAuteur  : Funto66Date    : 11/08/2013
Licence :
=========

Ce document intitulé « Heightmap opengl » issu de CommentCaMarche
(codes-sources.commentcamarche.net) est mis à disposition sous les termes de
la licence Creative Commons. Vous pouvez copier, modifier des copies de cette
source, dans les conditions fixées par la licence, tant que cette note
apparaît clairement.

Description :
=============

Utilisez les fl&egrave;ches pour vous d&eacute;placer. Si &ccedil;a ne marche pa
s chez vous essayez de recompiler (il vous faudra GLUT et OpenGL, que vous pouve
z trouver &agrave; <a href='http://site.voila.fr/allbrain/dev.zip' target='_blan
k'>http://site.voila.fr/allbrain/dev.zip</a> si vous utilisez Dev-C++ ou <a href
='http://site.voila.fr/allbrain/VisualC.zip' target='_blank'>http://site.voila.f
r/allbrain/VisualC.zip</a> si vous utilisez Visual C++)

<ul><li><ul><li><ul><
li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><
li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><
li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><
li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><
li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><li><ul><
li></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></
ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></
ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></
ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></
ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></
ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></ul></li></
ul></li></ul></li></ul></li></ul></li></ul></li></ul>
<br />
<br />C'est un sy
st&egrave;me de heightmaps; le principe, c'est qu'&agrave; partir d'une image 2D
 en niveaux de gris, on en ressort un terrain, o&ugrave; les points les plus hau
ts correspondent aux points les plus fonc&eacute;s de l'image 2D.
<br />Si je s
uis pas clair, regardez heightmap.bmp et le r&eacute;sultat de HeightMap.exe, et
 comparez...;)
<br />
<br />J'ai cr&eacute;&eacute; mon propre format de heigh
tmaps, le HMAP. En fait, il est compos&eacute; comme &ccedil;a :
<br />-le 1er 
octet renseigne sur l'endroit o&ugrave; d&eacute;butent les donn&eacute;es de la
 map
<br />-les 4 octets qui suivent repr&eacute;sentent, en little endian, la 
largeur et la hauteur de la map
<br />-apr&egrave;s on a le nom du fichier TGA 
associ&eacute; &agrave; la heightmap, qui lui sert de texture
<br />-enfin, il 
y a les donn&eacute;es proprement dites. Chaque pixel est cod&eacute; par 1 seul
 octet et le tout est compress&eacute; en RLE (m&ecirc;mes conventions que pour 
le format TGA).
<br />
<br />Pour enregister en HMAP il faut utiliser Alpha Ed
it &agrave; partir de la version 3.1. Si vous voulez cr&eacute;er vos propres he
ightmaps donc, c'est l&agrave; : <a href='http://www.cppfrance.com/code.aspx?ID=
24551' target='_blank'>http://www.cppfrance.com/code.aspx?ID=24551</a>
<br />(J
'ai pas pu mettre l'exe d'Alpha Edit dans le zip c'&eacute;tait trop gros :( )

<br /><a name='source-exemple'></a><h2> Source / Exemple : </h2>
<br /><pre cl
ass='code' data-mode='basic'>
Dans le zip
</pre>
<br /><a name='conclusion'><
/a><h2> Conclusion : </h2>
<br />Remerciements &agrave; cppdupdup34 pour m'avo
ir longuement expliqu&eacute; (j'ai mis longtemps &agrave; comprendre :p) commen
t est-ce qu'on fait pour faire un d&eacute;placement de la cam&eacute;ra &quot;&
agrave; la doom-like&quot;. En fait ce code est un morceau du code d'un jeu qu'o
n est en train de vous pr&eacute;parer :)
