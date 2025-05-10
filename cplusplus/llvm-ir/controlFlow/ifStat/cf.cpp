int main(int argc, char* argv[])
{
    int x;
    if (argc > 2) {
        x = argc;
    } else {
        x = -1;
    }

    x += 42;

    return x;
}
