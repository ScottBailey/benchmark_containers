# Container Benchmarks

## FIFO Lists

I have often had need of FIFO containers. Here we compare
`std::deque`, `std::vector`, and `boost::container::devector`.

I was somewhat surprised to see Boost's devector faired so poorly. In
prior testing I seem to recall it outperforming std::deque.
