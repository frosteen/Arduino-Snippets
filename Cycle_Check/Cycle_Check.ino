boolean cycle_check(unsigned long *last_millis, unsigned long cycle)
{
  unsigned long current_millis = millis();
  if (current_millis - *last_millis >= cycle)
  {
    *last_millis = current_millis;
    return true;
  }
  return false;
}
