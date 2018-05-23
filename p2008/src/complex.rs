const EPS: f64 = 1e-6;

#[derive(Debug, Copy, Clone)]
struct Complex {
    pub re: f64,
    pub im: f64,
}

impl Complex {
    fn new(re: f64, im: f64) -> Complex { Complex { re: re, im: im } }
}

impl Add<Complex> for Complex {
    type Output = Complex;
    fn add(self, other: Complex) -> Complex { Complex::new(self.re + other.re, self.im + other.im) }
}

impl Sub<Complex> for Complex {
    type Output = Complex;
    fn sub(self, other: Complex) -> Complex { Complex::new(self.re - other.re, self.im - other.im) }
}

impl Mul<f64> for Complex {
    type Output = Complex;
    fn mul(self, other: f64) -> Complex { Complex::new(self.re * other, self.im * other) }
}

impl Mul<Complex> for Complex {
    type Output = Complex;
    fn mul(self, other: Complex) -> Complex {
        Complex::new(self.re * other.re - self.im * other.im,
                     self.re * other.im + self.im * other.re)
    }
}

impl Complex {
    fn conj(&self) -> Complex { Complex::new(self.re, -self.im) }
    fn norm_sqr(&self) -> f64 { self.re * self.re + self.im * self.im }
    fn norm(&self) -> f64 { self.norm_sqr().sqrt() }
    /*
    fn inv(&self) -> Complex {
        let d = self.norm_sqr();
        Complex::new(self.re / d, -self.im / d)
    }
    */
    fn dot(&self, other: Complex) -> f64 {
        (self.conj() * other).re
    }
    /*
    fn cross(&self, other: Complex) -> f64 {
        (self.conj() * other).im
    }
    */
}

/*
fn ccw(a: Complex, b: Complex, c: Complex) -> i32 {
    let p = b - a;
    let q = c - a;
    if p.cross(q) > 0.0 { return 1; }
    if p.cross(q) < 0.0 { return -1; }
    if p.dot(q) < 0.0 { return 2; }
    if p.norm_sqr() < q.norm_sqr() { return -2; }
    return 0;
}
*/

fn projection(a: Complex, b: Complex, p: Complex) -> Complex {
    let t = (p - a).dot(a - b) / (a - b).norm();
    a + (a - b) * t
}

fn intersect_sp(a: Complex, b: Complex, p: Complex) -> bool {
    (a - p).norm() + (b - p).norm() - (b - a).norm() < EPS
}

/*
fn distance_sp(a: Complex, b: Complex, p: Complex) -> f64 {
    let r = projection(a, b, p);
    if intersect_sp(a, b, p) {
        (r - p).norm()
    } else {
        (a - p).norm().min((b - p).norm())
    }
}
*/
