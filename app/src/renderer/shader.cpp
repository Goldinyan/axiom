/*
 *Lädt die .vert und .frag Dateien, kompiliert sie auf der Grafikkarte und
 * verlinkt sie zu einem Shader-Programm. Er kümmert sich auch um die "Uniforms"
 * (z.B. die Rotations-Matrix an den Shader senden).
 */

/*
 *In der camera.cpp solltest du Spherical Coordinates (Sphärische Koordinaten)
 * verwenden. Anstatt X/Y/Z-Positionen direkt zu verschieben, speicherst du zwei
 * Winkel (Azymut und Polarwinkel) und einen Radius (Zoom). Das macht das
 * Kreisen um das Zentrum (den Nullpunkt des Plots) mathematisch viel einfacher
 * als freie Kamerabewegungen.
 */
