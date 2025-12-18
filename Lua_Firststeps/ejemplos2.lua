-- Para los comentarios en una linea 2 guiones
--[[
    con 2 guiones y 2 llaves se abren comentarios multilinea
]]--

num = 42 -- los numeros pueden ser int o floats indistintamente
t = "string"
s = 'string inmutable'
u = [[ Esto es 
        un string 
        multi linea
        ]]
t = nil

while num < 50 do
    num = num + 1 -- No existe los ++ --
end

if num > 40 then
    print('num over 40')
elseif s ~= 'no s' then
    io.write('not over 40\n') -- para escribir por la consola
end

thisIsGlobal = 20 -- las variables son globales por defecto
local read = io.read() -- lee de la entrada estandar
print(read)

-- las variables sin definir son nil
algo = sinDefinirEsNil


function fib(n)
    if n < 2 then return 1 end
    return fib(n - 2) + fib(n -1)
end

function adder(x)
    return function (y) return x + y end
end

a1 = adder(10);

print(a1(20))

