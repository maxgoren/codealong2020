int getrand(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

int min(int a, int b)
{
  if (a < b)
  {
    return a;
  } else {
    return b;
  }
}

int max(int a, int b)
{
  if (a > b)
  {
    return a;
  } else {
    return b;
  }
}
