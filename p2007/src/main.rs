use std::cmp::min;
use std::io::{Read, StdinLock};
use std::str::{from_utf8, FromStr};
use std::vec::Vec;

struct StdinReader<'a> {
    reader: StdinLock<'a>,
}

impl<'a> StdinReader<'a> {
    pub fn new(reader: StdinLock<'a>) -> StdinReader {
        StdinReader { reader: reader }
    }

    pub fn read<T: FromStr>(&mut self) -> T {
        fn is_whitespace(ch: u8) -> bool {
            ch == 0x20 || ch == 0x0a || ch == 0x0d
        }

        let token: Vec<u8> = self.reader
            .by_ref()
            .bytes()
            .map(|ch| ch.expect("failed to read a byte"))
            .skip_while(|ch| is_whitespace(*ch))
            .take_while(|ch| !is_whitespace(*ch))
            .collect();
        let token_str = from_utf8(&token)
            .unwrap_or_else(|_| panic!(format!("invalid utf8 sequence: {:?}", token)));
        token_str
            .parse()
            .unwrap_or_else(|_| panic!(format!("failed to parse input: {}", token_str)))
    }
}

static VALUES: [i32; 4] = [1, 5, 10, 50];

fn main() {
    let stdin = std::io::stdin();
    let mut reader = StdinReader::new(stdin.lock());

    let mut first_case = true;
    loop {
        // 入力
        let target = reader.read::<i32>() / 10;
        if target == 0 { break; }
        let coins: Vec<i32> = (0..4).map(|_| reader.read()).collect();

        // 財布の中の硬貨を全部使って払う
        let total = coins.iter().zip(VALUES.iter())
            .fold(0, |sum, (n, v)| sum + n * v);
        let mut answer = coins.clone();

        // 返ってくる硬貨を計算する
        let mut diff = total - target;
        let mut returned = vec![0; 4];
        for i in (0..4).rev() {
            returned[i] = diff / VALUES[i];
            diff -= returned[i] * VALUES[i];
        }

        // 支払った硬貨と返ってきた硬貨との間に重複があれば取り除く
        for i in 0..4 {
            answer[i] -= min(answer[i], returned[i]);
        }

        // 出力
        if first_case {
            first_case = false;
        } else {
            println!();
        }
        for i in 0..4 {
            if answer[i] > 0 {
                println!("{} {}", VALUES[i] * 10, answer[i]);
            }
        }
    }
}
