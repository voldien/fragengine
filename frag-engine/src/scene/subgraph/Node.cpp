#include"Scene/SubGraph/Node.h"
using namespace fragcore;
using namespace fragengine;

Node::Node() : ITree()
{
}

Node::~Node() {

}

// Node *Node::root() const {
// 	return ITree::root();
// }

// Node *Node::getParent() const {
// 	return ITree::getParent();
// }

// void Node::setParent(Node *parent) {
// 	ITree::setParent(parent);
// }

// unsigned int Node::getNumChildren() const {
// 	return ITree::getNumChildren();
// }

// void Node::addChild(Node *pchild) {
// 	ITree::addChild(pchild);
// }

// void Node::removeChild(int index) {
// 	ITree::removeChild(index);
// }

// Node *Node::getChild(int index) const {
// 	return ITree::getChild(index);
// }

// int Node::getNodeChildIndex(Node *node) {
// 	return ITree::getNodeChildIndex(node);
// }


//
//
//void Node::rotate(const Vector3& eular){
//	Quaternion rotation = Quaternion::createQuaternionOfAxis(
//			(float)HPM_DEG2RAD(eular.x()),
//			(float)HPM_DEG2RAD(eular.y()),
//			(float)HPM_DEG2RAD(eular.z()));
//	Quaternion rotat = this->getRotation() * rotation;
//	rotat.makeUnitQuaternion();
//	this->setRotation(rotat);
//}
//
//
//void Node::setPosition(const Vector3& pos){
//	int i;
//
//	/*	Update rest of the nodes.	*/
//	for(i = 0; i < this->getNumChildren(); i++){
//		Node* c = this->getChild(i);
//		//c->setPosition((getPosition() - pos) + c->getPosition());
//	}
//
//	this->pos = pos;
//}
//
//void Node::setLocalPosition(const Vector3& pos){
//
//}
//
//void Node::setScale(const Vector3& scale){
//	this->scale = scale;
//}
//void Node::setLocalScale(const Vector3& scale){
//
//}
//
//
//void Node::setRotation(const Quaternion& quat){
//	this->quat = quat;
//}
//
//void Node::setLocalRotation(const Quaternion& quat){
//
//	if(this->getParent()){
//		Vector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		Vector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//			//this->child(x)->SetLocalRotationTransformation(this->rotation,newrotat - old);
//		}
//	}
//	else{
//		Vector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		Vector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//		//	this->children[x]->SetLocalRotationTransformation(this->_rotation,old - newrotat);
//
//		}
//	}
//}
//
//const Quaternion &Node::getRotation() const {
//	if (getDynamicRef()->isAttached())
//		this->quat = getDynamicRef()->attachment->getOrientation();
//
//	return this->quat;
//}
//
//Quaternion Node::getLocalRotation() const {
//	if (!getDynamicRef()->isAttached())
//		return this->quat;
//	else
//		return getDynamicRef()->attachment->getOrientation();
//}
//
//
//Matrix4x4 Node::getMatrix() const {
//	return Matrix4x4::translate(this->getPosition()) *
//	       Matrix4x4::rotate(this->getRotation()) *
//	       Matrix4x4::scale(this->getScale());
//}
//
//Matrix4x4 Node::getLocalMatrix() const {
//	return Matrix4x4::translate(this->getLocalPosition()) *
//	       Matrix4x4::rotate(this->getLocalRotation()) *
//	       Matrix4x4::scale(this->getLocalScale());
//}
//
//Matrix4x4 Node::getViewMatrix() const {
//	/*  TODO resolve camera and non camerae view matrix.    */
//	return Matrix4x4::rotate(this->getRotation().conjugate()) *
//	       Matrix4x4::translate(-this->getPosition()) *
//	       Matrix4x4::scale(this->getScale());
//}
//
//Matrix4x4 Node::getViewLocalMatrix() const {
//	return Matrix4x4::translate(-this->getLocalPosition()) *
//	       Matrix4x4::rotate(this->getLocalRotation().conjugate()) *
//	       Matrix4x4::scale(-this->getLocalScale());
//}
//
//DynamicObjects* Node::getDynamicRef() {
//	return &this->ref;
//}
