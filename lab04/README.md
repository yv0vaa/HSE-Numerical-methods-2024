## Calculating $a_k$ analytically:
$$I(k) := \int_0^{\pi} e^x\cos{kx}\mathrm{d}x = e^x\cos{kx}|_0^{\pi} + k\int_0^{\pi}e^x\sin{kx}\mathrm{d}x = e^{\pi}(-1)^k - 1 - k(e^k\sin{kx}|_0^{\pi} - k\int_0^{\pi}e^x\cos{kx}\mathrm{d}x)$$
$\implies I(k) = e^{\pi}(-1)^k - 1 - k^2I(k) \implies I(k) = \frac{e^{\pi}(-1)^k - 1}{k^2 + 1}$
$$a_k = \frac{1}{\pi}I(k) = \frac{1}{\pi}\frac{e^{\pi}(-1)^k - 1}{k^2 + 1}$$
