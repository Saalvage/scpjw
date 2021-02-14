struct VS_INPUT {
    float2 position : POSITION0;
};

struct PS_INPUT {
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

struct PS_OUTPUT {
    float4 color : SV_Target0;
};

static float2 positions[3] = {
    float2(0.0, -0.5),
    float2(0.5, 0.5),
    float2(-0.5, 0.5)
};

static float3 colors[3] = {
    float3(1.0, 0.0, 0.0),
    float3(0.0, 1.0, 0.0),
    float3(0.0, 0.0, 1.0)
};

PS_INPUT VS(uint vid : SV_VertexID) {
    PS_INPUT output = (PS_INPUT)0;
    output.position = float4(positions[vid], 0.0, 1.0);
    output.color = float4(colors[vid], 1.0);
    return output;
}

PS_OUTPUT PS(PS_INPUT input) {
    PS_OUTPUT output = (PS_OUTPUT)0;
    output.color = input.color;
    return output;
}
