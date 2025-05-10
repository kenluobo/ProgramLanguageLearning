int add(int left, int right){
  return left + right;
}

int main(int argc, char* argv[]) {
  int x;
  while(argc-- > 0){
    if(argc % 2 == 0){
      x = add(x, x-1);
    } else {
      x = add(x, x+1);
    }
  }

  return x;
}
