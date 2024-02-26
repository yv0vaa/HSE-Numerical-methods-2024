## Calculating $a_k$ analytically:
$I(k) := \int_0^{\pi} e^x\cos{kx}\mathrm{d}x = e^x\cos{kx}|_0^{\pi} + k\int_0^{\pi}e^x\sin{kx}\mathrm{d}x = e^{\pi}(-1)^k - 1 - k(e^k\sin{kx}|_0^{\pi} - k\int_0^{\pi}e^x\cos{kx}\mathrm{d}x)$
Since
$\implies I(k) = e^{\pi}(-1)^k - 1 - k^2I(k) \implies I(k) = \frac{e^{\pi}(-1)^k - 1}{k^2 + 1}$
