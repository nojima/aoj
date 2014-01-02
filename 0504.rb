require 'bigdecimal'

def f(x)
  BigDecimal.new(x.to_s, $d)
end

loop do
  n, k, m, r = gets.split.map{|x| x.to_i}
  break if n == 0
  $d = r + 10
  ans = f(1) / f(n)
  if m == 1
    s = f(1)
    (1..n-1).each {|i| s += f(1) / f(i) }
    ans *= s
  end
  puts ans.to_s("F").ljust($d, "0")[0..r+1]
end
