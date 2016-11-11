#include "BaseLinkage.h"


PD::BaseLinkage::BaseLinkage(){
	axisResolution = 16; //default resolution
}

PD::BaseLinkage::~BaseLinkage(){
}

/* Updates the radius of the bank linkage with newRadius
 *
 * Example
 *
 *   arm.base.setRadius(22);
 */
void PD::BaseLinkage::setRadius(float newRadius){
	radius = newRadius;
	cylinder.setRadius(radius);
}

/* Updates the height of the base linkage with newHeight
 *
 * Example
 *
 *   arm.foreArmTwist.setHeight(16);
 */
void PD::BaseLinkage::setHeight(float newHeight){
	height = newHeight;
	cylinder.setHeight(height);
}

/* Updates the draw resolution (e.g. number of points on the circular base) with newResolution. (Note: default resolution is 16)
 *
 * Example
 *
 *   arm.base.setResolution(12);
 */
void PD::BaseLinkage::setResolution(int newResolution){
	axisResolution = newResolution;
	cylinder.setResolutionRadius(axisResolution);
}

/* Sets the color of the linkage (default greenYellow).
 *
 * Example
 *
 *   arm.setColor(ofColor::Red);
 */
void PD::BaseLinkage::setColor(ofColor newColor){
	color = newColor;
}

/* Instantiates a new instance of an arm with provided dimensions
 *
 * newRadius - defines the size of the circular base of the rectangular linkage
 * newHeight - defines the length of the cylindrical linkage
 * enableXray - enables or disables (disabled on default) showing the xyz gizmo (used for positioning and confirming rotation axis`)
 *
 * Example
 *
 * 
 */
void PD::BaseLinkage::setup(float newRadius, float newHeight, bool turnXRayOn){
	setRadius(newRadius);
	setHeight(newHeight);

	cylinder.set(radius, height);
	cylinder.setResolutionRadius(axisResolution);
	cylinder.setResolutionHeight(1);
	color = ofColor::greenYellow;
	fColor = ofFloatColor(.75, 1, .2,.5);
	material.setDiffuseColor(fColor);
	material.setShininess(.01);
	widget.setup(newRadius/4);
	if (turnXRayOn) {
		showXray();
	} else {
		disableXray();
	}
}

/* Draws the linkage onto the screen. 
 *
 * Example
 *
 *   
 */
void PD::BaseLinkage::draw(){
	//sets color of cylinder
	cylinder.setCylinderColor(color);
	cylinder.setTopCapColor(color);
	cylinder.setBottomCapColor(color);
	if (showWidget) {
		color.set(color.r, color.g, color.b, 200);
	}
	if (showWidget) {
		ofPushMatrix();
			ofRotateX(180);
			widget.draw();
		ofPopMatrix();
	}
	cylinder.draw();
}

/* Changes the alpha (transparency) for the linkage and enables a flag that draws the xyzWidget. 
 * Can be used in a callback function to enable certain (or all) the linkages for debugging. 
 *
 * Example
 *
 *   
 */
void PD::BaseLinkage::showXray(){
	showWidget = true;
}

/* Reverts the alpha (if it has changed) back to 0 transparency and disables the flag that draws the xyzWidget. 
 * Can be used with showXray to toggle transparency for certain (or all) the linkages for debugging.
 *
 * Example
 *
 *   
 */
void PD::BaseLinkage::disableXray(){
	showWidget = false;
}
