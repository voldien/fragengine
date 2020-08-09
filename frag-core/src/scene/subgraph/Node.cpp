#include"Scene/SubGraph/Node.h"
using namespace fragcore;

Node::Node(void) : ITree() {
}

Node::~Node(void) {

}

Node *Node::root(void) const {
	return ITree::root();
}

Node *Node::getParent(void) const {
	return ITree::getParent();
}

void Node::setParent(Node *parent) {
	ITree::setParent(parent);
}

unsigned int Node::getNumChildren(void) const {
	return ITree::getNumChildren();
}

void Node::addChild(Node *pchild) {
	ITree::addChild(pchild);
}

void Node::removeChild(int index) {
	ITree::removeChild(index);
}

Node *Node::getChild(int index) const {
	return ITree::getChild(index);
}

int Node::getNodeChildIndex(Node *node) {
	return ITree::getNodeChildIndex(node);
}


//
//
//void Node::rotate(const PVVector3& eular){
//	PVQuaternion rotation = PVQuaternion::createQuaternionOfAxis(
//			(float)HPM_DEG2RAD(eular.x()),
//			(float)HPM_DEG2RAD(eular.y()),
//			(float)HPM_DEG2RAD(eular.z()));
//	PVQuaternion rotat = this->getRotation() * rotation;
//	rotat.makeUnitQuaternion();
//	this->setRotation(rotat);
//}
//
//
//void Node::setPosition(const PVVector3& pos){
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
//void Node::setLocalPosition(const PVVector3& pos){
//
//}
//
//void Node::setScale(const PVVector3& scale){
//	this->scale = scale;
//}
//void Node::setLocalScale(const PVVector3& scale){
//
//}
//
//
//void Node::setRotation(const PVQuaternion& quat){
//	this->quat = quat;
//}
//
//void Node::setLocalRotation(const PVQuaternion& quat){
//
//	if(this->getParent()){
//		PVVector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		PVVector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//			//this->child(x)->SetLocalRotationTransformation(this->rotation,newrotat - old);
//		}
//	}
//	else{
//		PVVector3 old = this->getRotation().forward();
//		this->quat = quat * this->getRotation().conjugate() * this->getRotation(); // setRotation * getLocalRotation();
//		this->quat.makeUnitQuaternion();
//		PVVector3 newrotat = this->getRotation().forward();
//		for(unsigned int x = 0; x < this->getNumChildren(); x++){			//send transform position information to children.
//		//	this->children[x]->SetLocalRotationTransformation(this->_rotation,old - newrotat);
//
//		}
//	}
//}
//
//const PVQuaternion &Node::getRotation(void) const {
//	if (getDynamicRef()->isAttached())
//		this->quat = getDynamicRef()->attachment->getOrientation();
//
//	return this->quat;
//}
//
//PVQuaternion Node::getLocalRotation(void) const {
//	if (!getDynamicRef()->isAttached())
//		return this->quat;
//	else
//		return getDynamicRef()->attachment->getOrientation();
//}
//
//
//PVMatrix4x4 Node::getMatrix(void) const {
//	return PVMatrix4x4::translate(this->getPosition()) *
//	       PVMatrix4x4::rotate(this->getRotation()) *
//	       PVMatrix4x4::scale(this->getScale());
//}
//
//PVMatrix4x4 Node::getLocalMatrix(void) const {
//	return PVMatrix4x4::translate(this->getLocalPosition()) *
//	       PVMatrix4x4::rotate(this->getLocalRotation()) *
//	       PVMatrix4x4::scale(this->getLocalScale());
//}
//
//PVMatrix4x4 Node::getViewMatrix(void) const {
//	/*  TODO resolve camera and non camerae view matrix.    */
//	return PVMatrix4x4::rotate(this->getRotation().conjugate()) *
//	       PVMatrix4x4::translate(-this->getPosition()) *
//	       PVMatrix4x4::scale(this->getScale());
//}
//
//PVMatrix4x4 Node::getViewLocalMatrix(void) const {
//	return PVMatrix4x4::translate(-this->getLocalPosition()) *
//	       PVMatrix4x4::rotate(this->getLocalRotation().conjugate()) *
//	       PVMatrix4x4::scale(-this->getLocalScale());
//}
//
//DynamicObjects* Node::getDynamicRef(void) {
//	return &this->ref;
//}
