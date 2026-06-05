#version 300 es
precision mediump float;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

uniform sampler2D texture0;  // colormap
uniform sampler2D texture1;  // specularmap
uniform sampler2D texture2;  // nightmap

uniform vec3 lightPos;
uniform vec3 camPos;
uniform float isStar;

out vec4 finalColor;

void main() {
    vec4 color = texture(texture0, fragTexCoord);

    if (isStar > 0.5) {
        finalColor = color;
        return;
    }

    vec3 norm      = normalize(fragNormal);
    vec3 lightDir  = normalize(lightPos - fragPos);
    float diff     = dot(norm, lightDir);

    float ambient  = 0.02;
    float dayLight = max(diff, 0.0) + ambient;

    // city lights fade in at the terminator
    float nightFactor = smoothstep(0.15, -0.1, diff);
    vec3 nightLights  = texture(texture2, fragTexCoord).rgb * nightFactor;

    // Blinn-Phong specular masked by specular map (water)
    float specMask = texture(texture1, fragTexCoord).r;
    vec3 viewDir   = normalize(camPos - fragPos);
    vec3 halfDir   = normalize(lightDir + viewDir);
    float spec     = pow(max(dot(norm, halfDir), 0.0), 64.0) * specMask * max(diff, 0.0);

    vec3 lit = color.rgb * dayLight + nightLights + vec3(spec * 0.6);

    finalColor = vec4(lit, 1.0);
}
