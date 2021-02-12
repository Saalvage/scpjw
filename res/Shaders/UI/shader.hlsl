cbuffer cbMatrices {
    matrix projectionMatrix;
};

cbuffer cbFragment {
    float4 imageColor;
};

struct VS_INPUT {
    float2 position : POSITION0;
};

struct PS_INPUT {
    float4 position : SV_POSITION;
};

struct PS_OUTPUT {
    float4 color : SV_Target0;
};

PS_INPUT VS(VS_INPUT input) {
    PS_INPUT output = (PS_INPUT)0;
    output.position = float4(input.position.x, input.position.y, 0.5, 1.0);
    output.position = mul(output.position, projectionMatrix);
    return output;
}

PS_OUTPUT PS(PS_INPUT input) {
    PS_OUTPUT output = (PS_OUTPUT)0;
    output.color = imageColor;
    return output;
}
