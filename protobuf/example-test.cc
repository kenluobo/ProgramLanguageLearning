#include "example.pb.h"

using namespace myproto;

//=============================================
void test(){
  // todo
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Person person;
  person.set_id(123);
  person.add_emails("kkkk");
}

//=============================================
int main(){

}
