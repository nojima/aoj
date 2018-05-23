use std::io::{Read, StdinLock};
use std::str::{from_utf8, FromStr};
use std::vec::Vec;

const EPS: f64 = 1e-6;

struct StdinReader<'a> { reader: StdinLock<'a> }

impl<'a> StdinReader<'a> {
    pub fn new(reader: StdinLock<'a>) -> StdinReader { StdinReader { reader: reader } }
    pub fn read<T: FromStr>(&mut self) -> T {
        fn is_space(ch: u8) -> bool { ch == 0x20 || ch == 0x0a || ch == 0x0d }
        let b: Vec<u8> = self.reader.by_ref().bytes().map(|ch| ch.unwrap())
            .skip_while(|ch| is_space(*ch)).take_while(|ch| !is_space(*ch)).collect();
        let s = from_utf8(&b).unwrap();
        s.parse().unwrap_or_else(|_| panic!(format!("failed to parse: {}", s)))
    }
}

fn distance(p1: (f64, f64), p2: (f64, f64)) -> f64 {
    let dx = p1.0 - p2.0;
    let dy = p1.1 - p2.1;
    (dx * dx + dy * dy).sqrt()
}

fn dfs(visited: u32, p: (f64, f64), t: f64, crystals: &[(f64, f64)]) -> bool {
    let n = crystals.len();
    if visited == (1 << n) - 1 {
        return true;
    }

    // すべての頂点に到達可能かどうかをチェック
    for v in 0..n {
        if visited & (1 << v) != 0 { continue; }
        let q = crystals[v];
        let d = distance(p, q);
        if t + d >= distance(q, (0.0, 0.0)) - EPS {
            return false;
        }
    }

    for v in 0..n {
        if visited & (1 << v) != 0 { continue; }
        let q = crystals[v];
        let d = distance(p, q);
        if dfs(visited ^ (1 << v), q, t + d, crystals) {
            return true;
        }
    }
    false
}

fn main() {
    let stdin = std::io::stdin();
    let mut reader = StdinReader::new(stdin.lock());

    loop {
        let n: usize = reader.read();
        let hx: f64 = reader.read();
        let hy: f64 = reader.read();
        let dx: f64 = reader.read();
        let dy: f64 = reader.read();
        let start = (hx - dx, hy - dy);
        if n == 0 { break; }

        let mut crystals: Vec<(f64, f64)> = Vec::new();
        for _ in 0..n {
            let cx = reader.read::<f64>() - dx;
            let cy = reader.read::<f64>() - dy;
            crystals.push((cx, cy));
        }

        let ok = dfs(0, start, 0.0, &crystals);

        println!("{}", if ok { "YES" } else { "NO" });
    }
}
