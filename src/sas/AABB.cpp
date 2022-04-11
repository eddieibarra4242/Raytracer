/*
   Copyright 2022 Eduardo Ibarra

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "AABB.h"

constexpr uint8_t RIGHT = 0;
constexpr uint8_t LEFT = 1;
constexpr uint8_t MIDDLE = 2;

bool AABB::intersect(const Ray& ray) const
{
    /*
    Fast Ray-Box Intersection
    by Andrew Woo
    from "Graphics Gems", Academic Press, 1990

    Link: https://web.archive.org/web/20090803054252/http://tog.acm.org/resources/GraphicsGems/gems/RayBox.c
    */

    bool inside = true;
    uint8_t quadrant[3];
    float candidatePlane[3];

    /* Find candidate planes; this loop can be avoided if
       rays cast all from the eye(assume perspective view) */
    for (int i = 0; i < 3; i++) {
        if (ray.origin[i] < m_min[i]) {
            quadrant[i] = LEFT;
            candidatePlane[i] = m_min[i];
            inside = false;
        } else if (ray.origin[i] > m_max[i]) {
            quadrant[i] = RIGHT;
            candidatePlane[i] = m_max[i];
            inside = false;
        } else {
            quadrant[i] = MIDDLE;
        }
    }

    /* Ray origin inside bounding box */
    if(inside)	{
        return true;
    }

    /* Calculate T distances to candidate planes */
    float maxT[3];
    for (int i = 0; i < 3; i++) {
        if (quadrant[i] != MIDDLE && ray.direction[i] != 0.0f) {
            maxT[i] = (candidatePlane[i] - ray.origin[i]) / ray.direction[i];
        } else {
            maxT[i] = -1.0f;
        }
    }

    /* Get largest of the maxT's for final choice of intersection */
    int whichPlane = 0;
    for (int i = 1; i < 3; i++) {
        if (maxT[whichPlane] < maxT[i]) {
            whichPlane = i;
        }
    }

    float coord[3];

    /* Check final candidate actually inside box */
    if (maxT[whichPlane] < 0.0f) {
        return false;
    }

    for (int i = 0; i < 3; i++) {
        if (whichPlane != i) {
            coord[i] = ray.origin[i] + maxT[whichPlane] * ray.direction[i];

            if (coord[i] < m_min[i] || coord[i] > m_max[i]) {
                return false;
            }
        } else {
            coord[i] = candidatePlane[i];
        }
    }

    return true;				/* ray hits box */
}

void AABB::fit(const Sphere& s)
{
    glm::vec3 radVec {s.radius()};
    m_min = glm::min(m_min, s.position() - radVec);
    m_max = glm::max(m_max, s.position() + radVec);
}