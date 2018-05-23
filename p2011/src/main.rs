use std::io::{Read, StdinLock};
use std::mem;
use std::str::{from_utf8, FromStr};
use std::vec::Vec;

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

fn main() {
    let stdin = std::io::stdin();
    let mut reader = StdinReader::new(stdin.lock());

    loop {
        let n: usize = reader.read();
        if n == 0 { break; }

        let mut is_free = vec![vec![false; 30]; n];
        for i in 0..n {
            let f_i: usize = reader.read();
            for _ in 0..f_i {
                let d = reader.read::<usize>() - 1;
                is_free[i][d] = true;
            }
        }

        let mut curr: Vec<u64> = vec![0; n];
        let mut prev: Vec<u64> = vec![0; n];

        for i in 0..n {
            prev[i] = 1 << i;
        }

        let mut answer = -1;
        'outer: for t in 0..30 {
            for i in 0..n {
                // t日目にi番目の人が所有しうる地図の集合を求める
                if !is_free[i][t] {
                    curr[i] = prev[i];
                } else {
                    let mut set = prev[i];
                    for j in 0..n {
                        if i == j { continue; }
                        if !is_free[j][t] { continue; }
                        set |= prev[j];
                    }
                    curr[i] = set;
                }
            }
            for i in 0..n {
                if curr[i] == (1 << n) - 1 {
                    answer = (t + 1) as i64;
                    break 'outer;
                }
            }
            mem::swap(&mut curr, &mut prev);
        }

        println!("{}", answer);
    }
}
